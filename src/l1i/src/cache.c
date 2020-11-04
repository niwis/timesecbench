/*
 * File: cache.c
 * Project: src
 * Created Date: Friday July 24th 2020
 * Author: Ronan (ronan.lashermes@inria.fr)
 * -----
 * Last Modified: Tuesday, 28th July 2020 2:28:32 pm
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

void prime_l1i() {
    // the goal is:
    // 1 - fill an empty region of memory with ret instructions (0x00008067), that can be used to fill (one line per set) the cache
    // 2 - fill the L1I cache with the instructions in this memory area

    uint32_t add = I_LAST_LINE_ADD;
    uint32_t end_add = I_LAST_LINE_ADD - (I_SETS * I_WAYS * I_LINE_SIZE);
    while (add >= end_add) {
        write_u32((void*)add, 0x00008067);
        asm("jalr %[a]"
            :
            : [a] "r" (add)
            : "ra");
        add -= I_LINE_SIZE;
    }


    // for (uint32_t i = 0; i < I_SETS * I_WAYS; i++) {
        // uint32_t* add = (uint32_t*) I_LAST_LINE_ADD - (i * I_LINE_SIZE);
        // uint32_t* add = (uint32_t*)  (set_index * I_LINE_SIZE + w*(I_LINE_SIZE* I_SETS));
        // *add = 0x00008067;
        // *add = 0x67800000;
        // write_u32(add, 0x00008067);
        // prime_l1d();

        // asm("nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop");
        // touch_l1i_add((void*)add);

        // read_u32(add);
    //     asm("jalr %[a]"
    //         :
    //         : [a] "r" (add)
    //         :);
    // }
    // }
}

void touch_l1i_add(void* address) {
    asm("jalr %[a]"
            :
            : [a] "r" (address)
            : "ra");
    // address(); //expect a return instruction at address
}

uint32_t poke_l1i_add(void (*address)()) {
    uint32_t diff;
    asm(    "rdcycle s0\n"
            "jalr   %[add]\n"
            "rdcycle a0\n"
            "sub %[diff], a0, s0\n"

            : [diff] "=r" (diff)// output
            : [add] "r" (address) // input
            : "a0" , "s0", "ra"      //clobbered
            );
    return diff;
}