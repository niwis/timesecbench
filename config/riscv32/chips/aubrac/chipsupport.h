/*
 * File: chipsupport.h
 * Project: generic
 * Created Date: Wednesday November 4th 2020
 * Author: Ronan (ronan.lashermes@inria.fr)
 * -----
 * Last Modified: Wednesday, 4th November 2020 4:56:34 pm
 * Modified By: Ronan (ronan.lashermes@inria.fr>)
 * -----
 * Copyright (c) 2020 INRIA
 */

#ifndef CHIP_SUPPORT_H
#define CHIP_SUPPORT_H

// L1D dimensions
#define D_WAYS 2
#define D_SETS 8
#define D_LINE_SIZE 32
#define L1D_SIZE (D_LINE_SIZE * D_WAYS * D_SETS)
#define L1D_SET_SIZE (D_LINE_SIZE * D_WAYS)

#endif