/*
 * File: chipsupport.h
 * Project: generic
 * Created Date: Wednesday November 4th 2020
 * Author: Ronan (ronan.lashermes@inria.fr)
 * -----
 * Last Modified: Tuesday, 4th May 2021 4:23:48 pm
 * Modified By: Ronan (ronan.lashermes@inria.fr>)
 * -----
 * Copyright (c) 2020 INRIA
 */

#ifndef CHIP_SUPPORT_H
#define CHIP_SUPPORT_H

#include "../riscv.h"

// Global
#define RAM_SIZE 8192

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