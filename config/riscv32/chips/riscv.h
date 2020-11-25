/*
 * File: riscv.h
 * Project: riscv32
 * Created Date: Wednesday November 25th 2020
 * Author: Ronan (ronan.lashermes@inria.fr)
 * -----
 * Last Modified: Wednesday, 25th November 2020 4:08:34 pm
 * Modified By: Ronan (ronan.lashermes@inria.fr>)
 * -----
 * Copyright (c) 2020 INRIA
 */

#ifndef RISCV_H
#define RISCV_H

#define RET_OPCODE      0x00008067  // opcode for "ret"
#define BLT01_OPCODE    0xB54063    // opcode for "blt a0, a1, 0"

inline unsigned int encode_branch_offset(unsigned int offset) {
    unsigned int final = (offset >> 4) & 0x80;
    final |= (offset << 7) & 0xF00;
    final |= (offset << 20) & 0x7E000000;
    final |= (offset << 21) & 0x80000000;
    return final;
}

#endif