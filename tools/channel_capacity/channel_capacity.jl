using Pkg
Pkg.activate("channel_capacity")


using CSV
using DataFrames
using Evolutionary

test_path = "../../../../../verilator/timesecbench/results/ubtb_matrix.csv"
function load_timing_matrix(path::String)::Matrix{Float64}
    d = CSV.File(path; header=false) |> DataFrame
    return Matrix{Float64}(d)
end

function find_channel_capacity(path::String)
    tm = load_timing_matrix(path)
    find_channel_capacity(tm)
end

function find_channel_capacity(timing_matrix::Matrix{Float64})
    pm = tm2pm_min(timing_matrix)
    s = size(pm,2)

    f(d) = opt_fun(d, pm)
    init = ones(s) ./ s

    
    lx = zeros(s) # lower bound for values
    ux = ones(s) # upper bound for values
    
    c(x) = [ sum(x) ] # negative values are zeroed
    lc   = [ 1.0 ] # lower bound for constraint function
    uc   = [ 1.0 ]   # upper bound for constraint function
    con = WorstFitnessConstraints(lx, ux, lc, uc, c)

    ga = GA(populationSize  = 500,
            crossover       = uniformbin(0.1),
            # crossover       = intermediate(),
            crossoverRate   = 0.3,
            mutationRate    = 0.5,
            mutation        = mu(0.001),
            selection       = rouletteinv
            )

    e = Evolutionary.optimize(f, con, init, ga, 
        Evolutionary.Options(
            iterations=1000, 
            store_trace = true))

    println("Approximate capacity is $(round(1.0/e.minimum, digits=2)) bits per symbol")
    # confirmation evaluation
    c = capacity_eval(e.minimizer, pm)

    max_cap = log2(size(pm,1))
    max_cap = round(max_cap, digits=2)

    ratio = c/max_cap

    println("Confirmation: $(round(c, digits=2)) ($(round(ratio, digits=2)))")
    println("Max MI/capacity = $max_cap")
end

# function co(a::Vector{Float64}, b::Vector{Float64})::Vector{Float64}
#     return (a .+ b) ./ 2
# end

function mu(σ::Real = 1.0) # gaussian + normalize
    function mutation(recombinant::T) where {T <: AbstractVector}
        d = length(recombinant)
        recombinant .+= σ.*randn(d)
        recombinant = map(x-> abs(x), recombinant)
        sm = sum(recombinant)
        return recombinant ./ sm
    end
    return mutation
end

function opt_fun(x::Vector{Float64}, pm::Matrix{Float64})::Float64
    c = capacity_eval(x, pm)
    if c > 0
        return 1/c
    else
        return 1000
    end
end


function byte_probability_vector(vector::Array{Int64,1})::Array{Float64,1}
    map(i -> 
        count(x->x==i,
            vector),
        0:255
    ) ./ size(vector,1)
end


function shannon_entropy(vector::Array{Int64,1})::Float64

    p = byte_probability_vector(vector)

    -sum(i-> p[i] == 0 ? 0 : p[i]*log(2,p[i]), 1:256)

end

function shannon_entropy(vector::Array{Int64,2})::Float64
    d = Dict()
    (nrows, ncols) = size(vector)

    for i in 1:nrows
        current_count = get(d, vector[i,:], 0)
        d[vector[i,:]] = current_count + 1
    end

    p::Float64 = 0.0

    for (k, v) in d
        thisp = v/nrows
        p += thisp * log(2, thisp)
    end

    return -p
end

function tm2pm_min(tm::Array{Float64, 2})
    pm::Array{Float64, 2} = zeros(size(tm))
    mins = minimum(tm, dims=1)

    (nrows, ncols) = size(tm)

    for c in 1:ncols
        for r in 1:nrows
            if tm[r,c] <= mins[c]
                pm[r,c] = 1.0
            else
                pm[r,c] = 0.0
            end
        end
    end


    #normalize by column

    (rows, cols) = size(pm)
    s = sum(pm)

    if s != 0.0
        pm /= s
    end

    return pm
end

function pm2mi(pm::Array{Float64,2})
    (rows, cols) = size(pm)
    @assert rows == cols

    pr::Array{Float64, 1} = sum(pm, dims=2)[:]
    pc::Array{Float64, 1} = sum(pm, dims=1)[:]
    
    mi = 0.0

    for r in 1:rows
        for c in 1:cols
            if pm[r, c] == 0.0
                continue
            else
                mi += pm[r, c] * (log2(pm[r, c]) - log2(pc[c]) - log2(pr[r]))
            end
        end
    end

    return mi
end

function mi_eval(path::String)
    d = CSV.File(path; header=false) |> DataFrame
    tm = Matrix{Float64}(d)
    mi_eval(tm)
end

function mi_eval(timing_matrix::Matrix{Float64})
    pm = tm2pm_min(timing_matrix)
    mi = pm2mi(pm)

    max_mi = log2(size(pm,1))
    ratio = round(mi/max_mi, digits=2)
    mi = round(mi, digits=2)
    max_mi = round(max_mi, digits=2)

    println("MI = $mi ($ratio)")
    println("Max MI/capacity = $max_mi")
    println()
end

function conditional_from_joint(pm::Array{Float64, 2})
    py_x = copy(pm)
    (rows, cols) = size(pm)

    for c in 1:cols
        s = sum(py_x[:,c])
        if s > 0
            py_x[:,c] ./= s
        end
    end
    return py_x
end

function py_compute(y::Int64, px::Array{Float64,1}, py_x::Array{Float64, 2})
    (rows, cols) = size(py_x)
    
    sum = 0
    for c in 1:rows
        sum += py_x[y,c] * px[c]
    end
    return sum
end

function capacity_eval(px::Array{Float64,1}, pm::Array{Float64, 2})
    py_x = conditional_from_joint(pm)
    return capacity_eval_conditional(px, py_x)
end 

function capacity_eval_conditional(px::Array{Float64,1}, py_x::Array{Float64, 2})

    # normalize input dist px
    px ./= sum(px)
    (rows, cols) = size(py_x)

    s = 0

    # x cols, y rows
    for r in 1:rows
        py = py_compute(r, px, py_x)
        for c in 1:cols
            if py > 0 && py_x[r,c] > 0
                s += py_x[r,c] * px[c] * (log2(py_x[r,c]) - log2(py))
            end
        end
    end
    return s
end 

function rand_normalized(size::Int64)::Vector{Float64}
    v = rand(size)
    tot = sum(v)

    return v ./ tot
end

for f in ARGS
    println("Evaluating capacity for $f")
    find_channel_capacity(f)

    mi_eval(f)
end