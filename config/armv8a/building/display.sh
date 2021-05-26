#!/usr/bin/env nix-shell
#!nix-shell --pure -p gnuplot -i bash

SCRIPTPATH="$( cd "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"
RESULT_DIR="$SCRIPTPATH/results"
FIGURE_DIR="$SCRIPTPATH/figures"


# $1 Plot title
# $2 hex prefix (e.g. "ul1d")
function gen_heatmap_fig {
    gnuplot -c "$SCRIPTPATH/display_matrix.gnuplot" "$1" "$RESULT_DIR/$2_matrix.csv" "$FIGURE_DIR/$2.eps" $3 $4
}

gen_heatmap_fig "Unprotected L1D" "l1d" 2 8

# if [ -z $1 ]; then
#     gen_heatmap_fig "Unprotected L1D" "ul1d" 2 8
#     gen_heatmap_fig "Protected L1D" "pl1d" 2 8

#     gen_heatmap_fig "Unprotected L1I" "ul1i" 11 19
#     gen_heatmap_fig "Protected L1I" "pl1i" 11 19

#     gen_heatmap_fig "Unprotected BHT" "ubht" 27 39
#     gen_heatmap_fig "Protected BHT" "pbht" 27 39

#     gen_heatmap_fig "Unprotected BTB" "ubtb" 28 42
#     gen_heatmap_fig "Protected BTB" "pbtb" 28 42

#     # gen_heatmap_fig "Unprotected cross L1D" "ucl1d" 2 12
#     # gen_heatmap_fig "Protected cross L1D" "pcl1d" 2 12

#     # gen_heatmap_fig "Unprotected port contention" "upc" 0 0
#     # gen_heatmap_fig "Protected port contention" "ppc"
# else
#     gen_heatmap_fig "$1" "$2"
# fi