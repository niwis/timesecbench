/*
 * File: l1i.c
 * Project: l1i
 * Created Date: Tuesday November 24th 2020
 * Author: Ronan (ronan.lashermes@inria.fr)
 * -----
 * Last Modified: Wednesday, 25th November 2020 2:29:57 pm
 * Modified By: Ronan (ronan.lashermes@inria.fr>)
 * -----
 * Copyright (c) 2020 INRIA
 */

#include "support.h"
#include "l1i.h"

void prime_l1i() {
    // the goal is:
    // 1 - fill an empty region of memory with ret instructions (0x00008067), that can be used to fill (one line per set) the cache
    // 2 - fill the L1I cache with the instructions in this memory area

    uint32_t add = RET_ARR2;
    uint32_t end_add = RET_ARR2 + L1I_SIZE;

    //first write rets
    while (add < end_add) {
        write_u32((void*)add, RET_OPCODE);
        add += I_LINE_SIZE;
    }

    instructions_fence();

    // then execute rets
    add = RET_ARR2;
    while (add < end_add) {
        ((sig_fun*)add)();//convert address to function pointer, and call it
        add += I_LINE_SIZE;
    }
}

void touch_l1i_add(sig_fun* address) {
    address(); //expect a return instruction at address
}

//Alignement is required for precise time measurement: we do not want the fetch to interfere.
__attribute__ ((aligned (I_LINE_SIZE))) __attribute__ ((noinline)) volatile uint32_t poke_l1i_add(sig_fun* address) {
    uint32_t start = read_time();
    address();
    uint32_t end = read_time();
    return (end - start);
}

// try to communicate i to spy
volatile void trojan(uint32_t i) {
    touch_l1i_add((void *) (RET_ARR1 + i * I_LINE_SIZE) );
}

//try to read o in communication channel
volatile uint32_t spy(uint32_t o) {
    return poke_l1i_add((void *) (RET_ARR1 + o * I_LINE_SIZE) );
}

void prepare_trojan() {
    security_domain_switch(0);

    prime_l1i();
}

void prepare_spy() {
    security_domain_switch(1);
}

void initialise_benchmark() {
    for(uint32_t s = 0; s < I_SETS; s++) {
        uint32_t add = RET_ARR1 + s * I_LINE_SIZE;
        write_u32((void *) add, 0x00008067);
    }

    instructions_fence();
}

uint32_t get_input_symbols_count() {
    return I_SETS;
}

uint32_t get_output_symbols_count() {
    return I_SETS;
}