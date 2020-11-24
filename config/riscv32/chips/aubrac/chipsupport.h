/*
 * File: chipsupport.h
 * Project: generic
 * Created Date: Wednesday November 4th 2020
 * Author: Ronan (ronan.lashermes@inria.fr)
 * -----
 * Last Modified: Tuesday, 24th November 2020 12:05:53 pm
 * Modified By: Ronan (ronan.lashermes@inria.fr>)
 * -----
 * Copyright (c) 2020 INRIA
 */

#ifndef CHIP_SUPPORT_H
#define CHIP_SUPPORT_H

// Global
#define RAM_SIZE 8192
#define RET_INST 0x00008067

// L1D dimensions
//l1d assumes RAM size >= 2*L1D size
#define D_WAYS 2
#define D_SETS 8
#define D_LINE_SIZE 32
#define L1D_SIZE (D_LINE_SIZE * D_WAYS * D_SETS)
// #define L1D_SET_SIZE (D_LINE_SIZE * D_WAYS)
// #define D_LAST_LINE (RAM_SIZE/D_LINE_SIZE - 1)

#define I_WAYS 2
#define I_SETS 8
#define I_LINE_SIZE 64
#define I_LAST_LINE_ADD (RAM_SIZE - I_LINE_SIZE)

#define L1I_SIZE (I_LINE_SIZE * I_WAYS * I_SETS)
// #define L1I_SET_SIZE (I_LINE_SIZE * I_WAYS)

#endif