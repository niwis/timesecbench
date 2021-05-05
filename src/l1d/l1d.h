/*
 * File: l1d.h
 * Project: l1d
 * Created Date: Wednesday November 4th 2020
 * Author: Ronan (ronan.lashermes@inria.fr)
 * -----
 * Last Modified: Tuesday, 24th November 2020 11:04:25 am
 * Modified By: Ronan (ronan.lashermes@inria.fr>)
 * -----
 * Copyright (c) 2020 INRIA
 */

#ifndef L1D_H
#define L1D_H

#define D_WAYS 4
#define D_SETS 128
#define D_LINE_SIZE 32
#define I_LINE_SIZE 32


typedef unsigned int uint32_t;
typedef void volatile* ADDRESS;

volatile inline uint32_t touch_l1d_add(ADDRESS address);
volatile uint32_t poke_l1d_add(ADDRESS address);// __attribute__((always_inline));

#endif
