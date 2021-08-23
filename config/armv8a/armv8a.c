/*
 * File: armv8a.c
 * Project: riscv32
 * Created Date: Wednesday November 25th 2020
 * Author: Ronan (ronan.lashermes@inria.fr)
 * -----
 * Last Modified: Friday, 11th June 2021 9:35:51 am
 * Modified By: Ronan (ronan.lashermes@inria.fr>)
 * -----
 * Copyright (c) 2020 INRIA
 */

#include "armv8a.h"

unsigned int encode_branch_offset(unsigned int offset) {
    unsigned int final = (offset << 5) & 0xFFFFE0;
    return final;
}

unsigned int encode_jump_offset(unsigned int offset) {
    unsigned int imm = offset & 0xFF000;

    return imm;
}