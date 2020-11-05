/*
 * File: l1d.h
 * Project: l1d
 * Created Date: Wednesday November 4th 2020
 * Author: Ronan (ronan.lashermes@inria.fr)
 * -----
 * Last Modified: Thursday, 5th November 2020 11:28:39 am
 * Modified By: Ronan (ronan.lashermes@inria.fr>)
 * -----
 * Copyright (c) 2020 INRIA
 */

#ifndef L1D_H
#define L1D_H

typedef unsigned int uint32_t;
typedef void volatile* ADDRESS;

volatile inline uint32_t touch_l1d_add(ADDRESS address);
volatile uint32_t poke_l1d_add(ADDRESS address);// __attribute__((always_inline));

#endif