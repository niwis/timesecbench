/*
 * File: btb.c
 * Project: btb
 * Created Date: Thursday November 26th 2020
 * Author: Ronan (ronan.lashermes@inria.fr)
 * -----
 * Last Modified: Thursday, 26th November 2020 2:03:17 pm
 * Modified By: Ronan (ronan.lashermes@inria.fr>)
 * -----
 * Copyright (c) 2020 INRIA
 */

#include "support.h"
#include "btb.h"

// save the opcode for easy rewritings
uint32_t zero_jumps[BTB_ENTRIES];
uint32_t one_jumps[BTB_ENTRIES];

// ret_one and ret_zero content is not important, but they are two distinct jump destinations.
__attribute__ ((noinline)) volatile uint32_t ret_zero() {
    return 0;
}

__attribute__ ((noinline)) volatile uint32_t ret_one() {
    return 1;
}

// the training gadget is an array of "j [ret_zero]" (size = BTB_ENTRIES), terminating with a ret
volatile void write_training_gadget() {
   
    //write ret at the end
    uint32_t* ret_add = &(((uint32_t*)WORK_ADD2)[BTB_ENTRIES]);
    *ret_add = RET_OPCODE;

    
    uint32_t ret_zero_add = ((uint32_t) ret_zero);
    uint32_t ret_one_add = ((uint32_t) ret_one);

    for(uint32_t i = 0; i < BTB_ENTRIES; i++) {
        uint32_t* jadd = &(((uint32_t*)WORK_ADD2)[i]);
        zero_jumps[i] = J_OPCODE | encode_jump_offset(ret_zero_add - (uint32_t)jadd);
        one_jumps[i]  = J_OPCODE | encode_jump_offset(ret_one_add - (uint32_t)jadd);

        // *jadd = zero_jumps[i]; // not necessarily
    }
}

void init_btb(uint32_t passes) {
    //1 - rewrite "j ret_zero" everywhere
    for(uint32_t i = 0; i < BTB_ENTRIES; i++) {
        uint32_t* callsite = (uint32_t*) &(((uint32_t*)WORK_ADD2)[i]);
        *callsite = zero_jumps[i];
    }

    // 2 - train. Jump to jump in training gadget.
    for(uint32_t p = 0; p < passes; p++) {

        for(uint32_t i = 0; i < BTB_ENTRIES; i++) {
            sig_jump* j = (sig_jump*)  &(((uint32_t*)WORK_ADD2)[i]);
            j();
        }

    }
}




void touch_one_btb(uint32_t i) {
    //1 - rewrite "j ret_one"
    volatile uint32_t* touch_add = &(((uint32_t*)WORK_ADD2)[i]);
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
__attribute__ ((aligned (I_LINE_SIZE))) __attribute__ ((noinline)) uint32_t poke_one_btb(uint32_t i) {
    // volatile uint32_t* address = (uint32_t*)((uint32_t)training_btb) + (i << 2);
    volatile uint32_t* address = &(((uint32_t*)WORK_ADD2)[i]);

    //1 - rewrite "j ret_one"
    *address = one_jumps[i];
    instructions_fence();

    

    //2 - measure time
    sig_jump* j = (sig_jump*) address;
    uint32_t start = read_time();
    j();
    uint32_t end = read_time();
        
    //3 - rewrite "j ret_zero"
    *address = zero_jumps[i];
    instructions_fence();

    return (end - start);
}

// try to communicate i to spy
volatile void trojan(uint32_t i) {
    touch_one_btb(i);
}

//try to read o in communication channel
volatile uint32_t spy(uint32_t o) {
    return poke_one_btb(o);
}

void prepare_trojan() {
    security_domain_switch(0);
    init_btb(2);
}

void prepare_spy() {
    security_domain_switch(1);
}

void initialise_benchmark() {
    write_training_gadget();
}

uint32_t get_input_symbols_count() {
    return BTB_ENTRIES;
}

uint32_t get_output_symbols_count() {
    return BTB_ENTRIES;
}