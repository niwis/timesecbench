# Bin2hex

Python script to convert a bin file (from objcpy) to a hex file (expected by the SystemVerilog RAM implementation).

## Setup

```
pip3 install click
pip3 install pyelftools
```

## Usage

```
python3 elf2hex.py --input INPUT_PATH --output OUTPUT_PATH --wide 16
```