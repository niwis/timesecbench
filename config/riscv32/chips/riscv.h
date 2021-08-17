/*
 * File: riscv.h
 * Project: riscv32
 * Created Date: Wednesday November 25th 2020
 * Author: Ronan (ronan.lashermes@inria.fr)
 * -----
 * Last Modified: Friday, 11th June 2021 9:33:24 am
 * Modified By: Ronan (ronan.lashermes@inria.fr>)
 * -----
 * Copyright (c) 2020 INRIA
 */

#ifndef RISCV_H
#define RISCV_H

#include <stdint.h>

typedef void volatile* ADDRESS;
typedef uint32_t TIMECOUNT;
typedef uint32_t WORD;
typedef uint32_t INST;

#define RET_OPCODE      0x00008067  // opcode for "ret"
#define BLT01_OPCODE    0xB54063    // opcode for "blt a0, a1, 0"
#define J_OPCODE        0x6F        // opcode for "j 0" (direct jump)


inline unsigned int encode_branch_offset(unsigned int offset) {
    unsigned int final = (offset >> 4) & 0x80;
    final |= (offset << 7) & 0xF00;
    final |= (offset << 20) & 0x7E000000;
    final |= (offset << 21) & 0x80000000;
    return final;
}

inline unsigned int encode_jump_offset(unsigned int offset) {
    unsigned int imm = offset & 0xFF000;
    imm |= (offset << 11) & 0x80000000;
    imm |= (offset << 20) & 0x7FE00000;
    imm |= (offset << 9) & 0x00100000;
    return imm;
}

#endif