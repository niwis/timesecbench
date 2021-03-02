/*
 * File: l1i.h
 * Project: l1i
 * Created Date: Tuesday November 24th 2020
 * Author: Ronan (ronan.lashermes@inria.fr)
 * -----
 * Last Modified: Tuesday, 2nd March 2021 4:19:24 pm
 * Modified By: Ronan (ronan.lashermes@inria.fr>)
 * -----
 * Copyright (c) 2020 INRIA
 */

#ifndef L1I_H
#define L1I_H

// requires
// - I_SETS
// - RET_INST
// - I_LINE_SIZE
// - WORK_ADD1
// - WORK_ADD2

#define L1I_WORD_COUNT (L1I_SIZE/sizeof(uint32_t))

typedef unsigned int uint32_t;
typedef void volatile* ADDRESS;
typedef void sig_fun(void);

// A structure of the size of L1I where we can easily write instructions
typedef volatile struct {
    uint32_t returns[L1I_WORD_COUNT];
} __attribute__ ((aligned (I_LINE_SIZE)))
l1i_work_area;

volatile void prime_l1i(void);
volatile inline void touch_l1i_add(sig_fun* add);
volatile uint32_t poke_l1i_add(sig_fun* add);

volatile inline void write_u32(void* address, uint32_t value) {
    *((uint32_t volatile*)address) = value;
}

#endif