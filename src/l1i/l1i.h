/*
 * File: l1i.h
 * Project: l1i
 * Created Date: Tuesday November 24th 2020
 * Author: Ronan (ronan.lashermes@inria.fr)
 * -----
 * Last Modified: Wednesday, 26th May 2021 2:53:14 pm
 * Modified By: Ronan (ronan.lashermes@inria.fr>)
 * -----
 * Copyright (c) 2020 INRIA
 */

#ifndef L1I_H
#define L1I_H

#include "support.h"
// requires
// - I_SETS
// - RET_INST
// - I_LINE_SIZE
// - L1I_SIZE

#define L1I_WORD_COUNT (L1I_SIZE/sizeof(INST))


typedef void sig_fun(void);

// A structure of the size of L1I where we can easily write instructions
typedef volatile struct {
    INST returns[L1I_WORD_COUNT];
} __attribute__ ((aligned (I_LINE_SIZE)))
l1i_work_area;

void prime_l1i(void);
inline void touch_l1i_add(sig_fun* add);
volatile TIMECOUNT poke_l1i_add(sig_fun* add);

inline void write_u32(void* address, uint32_t value) {
    *((uint32_t volatile*)address) = value;
}

#endif