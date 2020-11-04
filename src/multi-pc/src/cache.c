/*
 * File: cache.c
 * Project: src
 * Created Date: Friday July 24th 2020
 * Author: Ronan (ronan.lashermes@inria.fr)
 * -----
 * Last Modified: Monday, 31st August 2020 10:40:20 am
 * Modified By: Ronan (ronan.lashermes@inria.fr>)
 * -----
 * Copyright (c) 2020 INRIA
 */

#include "cache.h"
#include "gadgets.h"

const uint32_t ret = 0x00008067;
const uint32_t nop = 0x13;
const uint32_t jump_minus4 = 0xffdff06f;

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
    void* add = (void*)D_LAST_LINE_ADD;
    // for (uint32_t w = 0; w < D_WAYS; w++) {
        for (uint32_t s = 0; s < D_SETS*D_WAYS; s++) {
            // read_u32((void*) D_LAST_LINE_ADD - s*D_LINE_SIZE - w*(D_LINE_SIZE* D_SETS));
            read_u32(add);
            add = (void*)((uint32_t) add - D_LINE_SIZE);
        }
    // }
}


void wait_for_spy_sync() {
    wait_for_spy_sync_loop();

    //reset waiter
    //point to jump instruction
    uint32_t* add = &((uint32_t*)wait_for_spy_sync_loop)[1];
    *add = jump_minus4;
}

void wait_for_trojan_sync() {
    wait_for_trojan_sync_loop();

    //reset waiter
    //point to jump instruction
    uint32_t* add = &((uint32_t*)wait_for_trojan_sync_loop)[1];
    *add = jump_minus4;
}

void trojan_sync() {
    //point to jump instruction
    uint32_t* add = &((uint32_t*)wait_for_trojan_sync_loop)[1];
    pseudo_atomic_ret_write((void*)add);
    // *add = ret;
}

void spy_sync() {
    //point to jump instruction
    uint32_t* add = &((uint32_t*)wait_for_spy_sync_loop)[1];
    pseudo_atomic_ret_write((void*)add);
    // *add = ret;
}