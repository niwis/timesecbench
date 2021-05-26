/*
 * File: l1i.c
 * Project: l1i
 * Created Date: Tuesday November 24th 2020
 * Author: Ronan (ronan.lashermes@inria.fr)
 * -----
 * Last Modified: Wednesday, 26th May 2021 2:54:11 pm
 * Modified By: Ronan (ronan.lashermes@inria.fr>)
 * -----
 * Copyright (c) 2020 INRIA
 */

#include "support.h"
#include "l1i.h"

l1i_work_area area1;
l1i_work_area area2;

void prime_l1i() {
    // the goal is:
    // 1 - fill an empty region of memory with ret instructions (0x00008067), that can be used to fill (one line per set) the cache
    // 2 - fill (one line per set) of the L1I cache with the instructions in this memory area
    
    // //first write rets
    for(WORD s = 0; s < I_SETS; s++) {
        area2.returns[s*I_LINE_SIZE] = RET_OPCODE;
    }

    instructions_fence();

    // then execute rets
    for(WORD s = 0; s < I_SETS; s++) {
        ((sig_fun*)&(area2.returns[s*I_LINE_SIZE]))();//convert address to function pointer, and call it
    }
}

void touch_l1i_add(sig_fun* address) {
    address(); //expect a return instruction at address
}

//Alignement is required for precise time measurement: we do not want the fetch to interfere.
__attribute__ ((aligned (I_LINE_SIZE))) __attribute__ ((noinline)) volatile TIMECOUNT poke_l1i_add(sig_fun* address) {
    TIMECOUNT start = read_time();
    address();
    TIMECOUNT end = read_time();
    return (end - start);
}

// try to communicate i to spy
volatile void trojan(WORD i) {
    touch_l1i_add((void *) &(area1.returns[i * I_LINE_SIZE]) );
}

//try to read o in communication channel
volatile TIMECOUNT spy(WORD o) {
    return poke_l1i_add((void *) &(area1.returns[o * I_LINE_SIZE]) );
}

void prepare_trojan() {
    security_domain_switch(0);

    prime_l1i();
}

void prepare_spy() {
    security_domain_switch(1);
}

void initialise_benchmark() {


    for(WORD s = 0; s < I_SETS; s++) {
        area1.returns[s*I_LINE_SIZE] = RET_OPCODE;
    }

    instructions_fence();
}

WORD get_input_symbols_count() {
    return I_SETS;
}

WORD get_output_symbols_count() {
    return I_SETS;
}