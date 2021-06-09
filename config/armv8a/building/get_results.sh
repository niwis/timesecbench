SCRIPTPATH="$( cd "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"
RESULT_DIR="$SCRIPTPATH/results"

mkdir -p $RESULT_DIR

scp pierre@192.168.0.2:/home/pierre/benchmarks/results/* $RESULT_DIR
