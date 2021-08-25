# Channel capacity evaluation

This script tries to evaluate APPROXIMATELY the channel capacity of the files in input.
Uses a genetic algorithm.
Running the script twices may not yield the same results, but they should be close.

## Usage

```
julia channel_capacity.jl xxx_results.csv
```

The CSV files should be a timing matrix from timesecbench.