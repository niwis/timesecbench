/*
 * File: cache.c
 * Project: src
 * Created Date: Friday July 24th 2020
 * Author: Ronan (ronan.lashermes@inria.fr)
 * -----
 * Last Modified: Monday, 27th July 2020 3:06:39 pm
 * Modified By: Ronan (ronan.lashermes@inria.fr>)
 * -----
 * Copyright (c) 2020 INRIA
 */

#include "cache.h"
#include "gadgets.h"


void touch_l1d_add(void* address) {
    read_u32((void*)address);
}

uint32_t poke_l1d_add(void* address) {
    uint32_t diff;
    asm(    "rdcycle s0\n"
            "lw  a0, 0(%[add])\n"
            "rdcycle a0\n"
            "sub %[diff], a0, s0\n"

            : [diff] "=r" (diff)// output
            : [add] "r" (address) // input
            : "a0" , "s0"      //clobbered
            );
    return diff;

    // uint32_t start = read_time();
    // read_u32((void*) address);
    // uint32_t end = read_time();
    // return (end - start);
}

void prime_l1d() {
    for (uint32_t w = 0; w < D_WAYS; w++) {
        for (uint32_t s = 0; s < D_SETS; s++) {
            read_u32((void*) D_LAST_LINE_ADD - s*D_LINE_SIZE - w*(D_LINE_SIZE* D_SETS));
        }
    }
}