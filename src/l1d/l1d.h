/*
 * File: l1d.h
 * Project: l1d
 * Created Date: Wednesday November 4th 2020
 * Author: Ronan (ronan.lashermes@inria.fr)
 * -----
 * Last Modified: Wednesday, 4th November 2020 5:02:23 pm
 * Modified By: Ronan (ronan.lashermes@inria.fr>)
 * -----
 * Copyright (c) 2020 INRIA
 */

#ifndef L1D_H
#define L1D_H

typedef unsigned int uint32_t;
typedef void* ADDRESS;

volatile uint32_t touch_l1d_add(ADDRESS address) __attribute__((always_inline));
volatile uint32_t poke_l1d_add(ADDRESS address) __attribute__((always_inline));

#endif