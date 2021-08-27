#!/usr/bin/env nix-shell
#!nix-shell --pure -p gnuplot -i bash

SCRIPTPATH="$( cd "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"
RESULT_DIR="$SCRIPTPATH/results"
FIGURE_DIR="$SCRIPTPATH/figures"

mkdir -p $FIGURE_DIR

# $1 Plot title
# $2 hex prefix (e.g. "ul1d")
function gen_heatmap_fig {
    gnuplot -c "$SCRIPTPATH/display_matrix.gnuplot" "$1" "$RESULT_DIR/$2_matrix.csv" "$FIGURE_DIR/$2.eps" $3 $4
}

gen_heatmap_fig "L1D" "l1d" 20 22
# gen_heatmap_fig "L1I" "l1i" 0 30
# gen_heatmap_fig "BHT" "bht" 4 22
