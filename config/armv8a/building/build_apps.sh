SCRIPTPATH="$( cd "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"
BIN_DIR="$SCRIPTPATH/bin"

ROOT_PATH="$(realpath "$SCRIPTPATH/../../..")"

# TESTS="l1d	\
# 		l1i \
# 		bht \
# 		btb"

TESTS="l1d"

cd $SCRIPTPATH

mkdir -p $BIN_DIR

python3 $ROOT_PATH/build_all.py --arch armv8a --chip bcm2837 --board rpi3 --clean

