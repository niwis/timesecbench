/*
 * File: btb.c
 * Project: btb
 * Created Date: Thursday November 26th 2020
 * Author: Ronan (ronan.lashermes@inria.fr)
 * -----
 * Last Modified: Wednesday, 26th May 2021 2:52:09 pm
 * Modified By: Ronan (ronan.lashermes@inria.fr>)
 * -----
 * Copyright (c) 2020 INRIA
 */

#include "support.h"
#include "btb.h"

btb_work_area area;

// save the opcode for easy rewritings
uint32_t zero_jumps[BTB_ENTRIES];
uint32_t one_jumps[BTB_ENTRIES];

// ret_one and ret_zero content is not important, but they are two distinct jump destinations.
__attribute__ ((noinline)) volatile WORD ret_zero() {
    return 0;
}

__attribute__ ((noinline)) volatile WORD ret_one() {
    return 1;
}

// the training gadget is an array of "j [ret_zero]" (size = BTB_ENTRIES), terminating with a ret
volatile void write_training_gadget() {
   
    //write ret at the end
    area.entries[BTB_ENTRIES] = RET_OPCODE;
    
    WORD ret_zero_add = ((WORD) ret_zero);
    WORD ret_one_add = ((WORD) ret_one);

    for(WORD i = 0; i < BTB_ENTRIES; i++) {
        WORD* jadd = &(area.entries[i]);
        zero_jumps[i] = J_OPCODE | encode_jump_offset(ret_zero_add - (WORD)jadd);
        one_jumps[i]  = J_OPCODE | encode_jump_offset(ret_one_add - (WORD)jadd);

        // *jadd = zero_jumps[i]; // not necessary here
    }
}

void init_btb(WORD passes) {
    //1 - rewrite "j ret_zero" everywhere
    for(WORD i = 0; i < BTB_ENTRIES; i++) {
        WORD* callsite = (WORD*) &(area.entries[i]);
        *callsite = zero_jumps[i];
    }

    // 2 - train. Jump to jump in training gadget.
    for(WORD p = 0; p < passes; p++) {

        for(WORD i = 0; i < BTB_ENTRIES; i++) {
            sig_jump* j = (sig_jump*)  &(area.entries[i]);
            j();
        }

    }
}




void touch_one_btb(WORD i) {
    //1 - rewrite "j ret_one"
    volatile WORD* touch_add = &(area.entries[i]);
    *touch_add = one_jumps[i];
    instructions_fence();

    //2- execute jump
    sig_jump* j = (sig_jump*) touch_add;
    j();

    //3 - rewrite "j ret_zero"
    *touch_add = zero_jumps[i];
    instructions_fence();
}

//Alignement is required for precise time measurement: we do not want the fetch to interfere.
__attribute__ ((aligned (I_LINE_SIZE))) __attribute__ ((noinline)) TIMECOUNT poke_one_btb(WORD i) {
    // volatile uint32_t* address = (uint32_t*)((uint32_t)training_btb) + (i << 2);
    volatile WORD* address = &(area.entries[i]);

    //1 - rewrite "j ret_one"
    *address = one_jumps[i];
    instructions_fence();

    

    //2 - measure time
    sig_jump* j = (sig_jump*) address;
    TIMECOUNT start = read_time();
    j();
    TIMECOUNT end = read_time();
        
    //3 - rewrite "j ret_zero"
    *address = zero_jumps[i];
    instructions_fence();

    return (end - start);
}

// try to communicate i to spy
volatile void trojan(WORD i) {
    touch_one_btb(i);
}

//try to read o in communication channel
volatile TIMECOUNT spy(WORD o) {
    return poke_one_btb(o);
}

void prepare_trojan() {
    security_domain_switch(0);
    init_btb(1);
}

void prepare_spy() {
    security_domain_switch(1);
}

void initialise_benchmark() {
    write_training_gadget();
}

WORD get_input_symbols_count() {
    return BTB_ENTRIES;
}

WORD get_output_symbols_count() {
    return BTB_ENTRIES;
}