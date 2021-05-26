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

#define L1D_WORD_COUNT (L1D_SIZE/sizeof(uint64_t))

// A structure of the size of L1I where we can easily write instructions
typedef volatile struct {
    uint64_t words[L1D_WORD_COUNT];
} __attribute__ ((aligned (I_LINE_SIZE)))
l1d_work_area;


typedef unsigned int uint32_t;
typedef void volatile* ADDRESS;

volatile inline uint32_t touch_l1d_add(ADDRESS address);
volatile uint32_t poke_l1d_add(ADDRESS address);// __attribute__((always_inline));

#endif
