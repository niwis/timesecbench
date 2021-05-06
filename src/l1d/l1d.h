/*
 * File: l1d.h
 * Project: l1d
 * Created Date: Wednesday November 4th 2020
 * Author: Ronan (ronan.lashermes@inria.fr)
 * -----
 * Last Modified: Thursday, 6th May 2021 9:59:54 am
 * Modified By: Ronan (ronan.lashermes@inria.fr>)
 * -----
 * Copyright (c) 2020 INRIA
 */

#ifndef L1D_H
#define L1D_H

// requires
// - D_SETS
// - D_WAYS
// - D_LINE_SIZE
// - I_LINE_SIZE


typedef unsigned int uint32_t;
typedef void volatile* ADDRESS;

volatile inline uint32_t touch_l1d_add(ADDRESS address);
volatile uint32_t poke_l1d_add(ADDRESS address);// __attribute__((always_inline));

#endif
