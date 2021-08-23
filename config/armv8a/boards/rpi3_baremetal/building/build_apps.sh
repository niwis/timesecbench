SCRIPTPATH="$( cd "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"
BIN_DIR="$SCRIPTPATH/bin"

ROOT_PATH="$(realpath "$SCRIPTPATH/../../..")"

 TESTS="l1d	\
 		l1i \
 		bht \
 		btb"

cd $SCRIPTPATH

mkdir -p $BIN_DIR
mkdir -p $ROOT_PATH/list

python3 $ROOT_PATH/build_all.py --arch armv8a --chip bcm2837 --board rpi3_baremetal --clean

for test in $TESTS; do
	mv $ROOT_PATH/bd/src/$test/$test $BIN_DIR/$test
	aarch64-elf-objdump -d $BIN_DIR/$test > $ROOT_PATH/list/$test.list
done