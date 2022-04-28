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
    // execute rets
    for (int w = 0; w < I_WAYS; ++w) {
        for(WORD s = 0; s < I_SETS; s++) {
            ((sig_fun*)&(area2.returns[s*I_LINE_WORD_COUNT + w*I_SETS*I_LINE_WORD_COUNT]))();//convert address to function pointer, and call it
        }
    }
}

void touch_l1i_add(sig_fun* address) {
    address(); //expect a return instruction at address
}

//Alignement is required for precise time measurement: we do not want the fetch to interfere.
__attribute__ ((aligned (I_LINE_SIZE))) __attribute__ ((noinline)) volatile TIMECOUNT poke_l1i_add(sig_fun* address) {
    // address(); // cache instruction
    TIMECOUNT start = read_time();
    address();
    TIMECOUNT end = read_time();
    return (end - start);
}
// try to communicate i to spy
void trojan(WORD i) {
    touch_l1i_add((void *) &(area1.returns[i * I_LINE_WORD_COUNT]) );
}

//try to read o in communication channel
TIMECOUNT spy(WORD o) {
    return poke_l1i_add((void *) &(area1.returns[o * I_LINE_WORD_COUNT]) );
}

void prepare_trojan() {
    security_domain_switch(0);
    
    prime_l1i();
}

void prepare_spy() {
    security_domain_switch(1);
    // asm volatile (".word 0xfffff00b"); // fence.t
}

void initialise_benchmark() {
    for (int w = 0; w < I_WAYS; ++w) {
        for(WORD s = 0; s < I_SETS; s++) {
            area1.returns[s*I_LINE_WORD_COUNT + w*I_SETS*I_LINE_WORD_COUNT] = RET_OPCODE;
            area2.returns[s*I_LINE_WORD_COUNT + w*I_SETS*I_LINE_WORD_COUNT] = RET_OPCODE;
        }
    }
    instructions_fence();
}

WORD get_input_symbols_count() {
    return I_SETS;
}

WORD get_output_symbols_count() {
    return I_SETS;
}