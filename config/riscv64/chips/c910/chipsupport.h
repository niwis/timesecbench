/*
 * File: chipsupport.h
 * Project: generic
 * Created Date: Wednesday November 4th 2020
 * Author: Ronan (ronan.lashermes@inria.fr)
 * -----
 * Last Modified: Wednesday, 3rd March 2021 11:44:14 am
 * Modified By: Ronan (ronan.lashermes@inria.fr>)
 * -----
 * Copyright (c) 2020 INRIA
 */

#ifndef CHIP_SUPPORT_H
#define CHIP_SUPPORT_H

#include "../riscv.h"

// Global
#define RAM_SIZE 1000000000 // not used?

// L1D dimensions
//l1d assumes RAM size >= 2*L1D size
#define D_WAYS 2*2
#define D_SETS 512
#define D_LINE_SIZE 64 // in bytes
#define L1D_SIZE (D_LINE_SIZE * D_WAYS * D_SETS)

// L1I dimensions
#define I_WAYS 2
#define I_SETS 512
#define I_LINE_SIZE 64 // in bytes
#define L1I_SIZE (I_LINE_SIZE * I_WAYS * I_SETS)

// BHT dimensions
#define BHT_ENTRIES 64
#define BHT_COUNTER_BITS    2 //to evaluate the number of passes for training

// BTB dimensions
#define BTB_ENTRIES 16

// L2 configuration registers (64 bits)
#define L2_REG_MISS_COUNT 0x50000030
#define L2_REG_HIT_COUNT 0x50000028
#define L2_REG_PCNT_CFG 0x50000010
// L2 cache parameters
#define L2_REG_SET_ASSO 0x50000060
#define L2_REG_NO_LINES 0x50000068
#define L2_REG_NO_BLOCKS 0x50000070


#endif