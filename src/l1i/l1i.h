/*
 * File: l1i.h
 * Project: l1i
 * Created Date: Tuesday November 24th 2020
 * Author: Ronan (ronan.lashermes@inria.fr)
 * -----
 * Last Modified: Tuesday, 24th November 2020 3:38:21 pm
 * Modified By: Ronan (ronan.lashermes@inria.fr>)
 * -----
 * Copyright (c) 2020 INRIA
 */

#ifndef L1I_H
#define L1I_H

typedef unsigned int uint32_t;
typedef void volatile* ADDRESS;
typedef void sig_fun(void);

#define RET_ARR1 0x1400
#define RET_ARR2 0x1800

volatile void prime_l1i(void);
volatile inline void touch_l1i_add(sig_fun* add);
volatile uint32_t poke_l1i_add(sig_fun* add);

volatile inline void write_u32(void* address, uint32_t value) {
    *((uint32_t volatile*)address) = value;
}

#endif