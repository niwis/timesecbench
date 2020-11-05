/*
 * File: chipsupport.h
 * Project: generic
 * Created Date: Wednesday November 4th 2020
 * Author: Ronan (ronan.lashermes@inria.fr)
 * -----
 * Last Modified: Thursday, 5th November 2020 11:40:52 am
 * Modified By: Ronan (ronan.lashermes@inria.fr>)
 * -----
 * Copyright (c) 2020 INRIA
 */

#ifndef CHIP_SUPPORT_H
#define CHIP_SUPPORT_H

// Global
#define RAM_SIZE 8192

// L1D dimensions
//l1d assumes RAM size >= 2*L1D size
#define D_WAYS 2
#define D_SETS 8
#define D_LINE_SIZE 32
#define L1D_SIZE (D_LINE_SIZE * D_WAYS * D_SETS)
#define L1D_SET_SIZE (D_LINE_SIZE * D_WAYS)
#define D_LAST_LINE (RAM_SIZE/D_LINE_SIZE - 1)

#endif