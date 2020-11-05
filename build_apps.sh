#!/usr/bin/env nix-shell
#!nix-shell -i bash

SCRIPTPATH="$( cd "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"
HEX_DIR="$SCRIPTPATH/build/hex"

ROOT_PATH="$(realpath "$SCRIPTPATH")"
ELF2HEX_DIR="$(realpath "$ROOT_PATH/tools/elf2hex")"

TESTS="l1d"

cd $SCRIPTPATH

rm -rf list bd
mkdir -p $HEX_DIR
mkdir -p list

./build_all.py --arch riscv32 --chip aubrac --board aubrac --cc riscv32-inria-elf-gcc --cflags="-c -march=rv32im -mabi=ilp32 -O2 -ffunction-sections -fdata-sections" --ld riscv32-inria-elf-gcc --ldflags="-Wl,-gc-sections,-T,${ROOT_PATH}/config/riscv32/boards/aubrac/script-riscv32.ld" --user-libs="-lm" --clean

for test in $TESTS; do
	rm $HEX_DIR/${test}.hex 2> /dev/null
	python3 ${ELF2HEX_DIR}/elf2hex.py --input bd/src/$test/$test --output $HEX_DIR/$test.hex --wide 16
	riscv32-inria-elf-objdump -D bd/src/$test/$test > list/$test.list
done
