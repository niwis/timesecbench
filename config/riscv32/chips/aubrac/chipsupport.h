/*
 * File: chipsupport.h
 * Project: generic
 * Created Date: Wednesday November 4th 2020
 * Author: Ronan (ronan.lashermes@inria.fr)
 * -----
 * Last Modified: Thursday, 26th November 2020 2:24:10 pm
 * Modified By: Ronan (ronan.lashermes@inria.fr>)
 * -----
 * Copyright (c) 2020 INRIA
 */

#ifndef CHIP_SUPPORT_H
#define CHIP_SUPPORT_H

#include "../riscv.h"

// Global
#define RAM_SIZE 8192

#define WORK_SIZE 0x400  // max (L1I_SIZE, L1D, SIZE, BHT_ENTRIES*4+4, BTB_ENTRIES*4)
#define WORK_ADD1 0x1400 //somewhere where memory is free and available between this add and add + 2 * worksize
#define WORK_ADD2 (WORK_ADD1 + WORK_SIZE)

// L1D dimensions
//l1d assumes RAM size >= 2*L1D size
#define D_WAYS 2
#define D_SETS 8
#define D_LINE_SIZE 32
#define L1D_SIZE (D_LINE_SIZE * D_WAYS * D_SETS)

// L1I dimensions
#define I_WAYS 2
#define I_SETS 8
#define I_LINE_SIZE 64
#define L1I_SIZE (I_LINE_SIZE * I_WAYS * I_SETS)

// BHT dimensions
#define BHT_ENTRIES 128
#define BHT_COUNTER_BITS    2 //to evaluate the number of passes for training

// BTB dimensions
#define BTB_ENTRIES 32


#endif