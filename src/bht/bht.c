/*
 * File: bht.c
 * Project: bht
 * Created Date: Wednesday November 25th 2020
 * Author: Ronan (ronan.lashermes@inria.fr)
 * -----
 * Last Modified: Wednesday, 3rd March 2021 11:19:00 am
 * Modified By: Ronan (ronan.lashermes@inria.fr>)
 * -----
 * Copyright (c) 2020 INRIA
 */

#include "support.h"
#include "bht.h"

bht_work_area area1;
volatile uint32_t dummy;

// the training gadget is an array of "blt a0, a1, [gadget_end]" (size = BHT_ENTRIES), terminating with a ret
// if we execute one instruction, it will be the only branch to be taken if the condition is met, or all successive branches will be taken if not met.
volatile void write_training_gadget() {
    //write ret at the end
    // uint32_t* ret_add = &(((uint32_t*)WORK_ADD2)[BHT_ENTRIES]);
    // *ret_add = RET_OPCODE;
    area1.entries[BHT_ENTRIES] = RET_OPCODE;
    uint32_t off0_val = BLT01_OPCODE;

    for(uint32_t i = 0; i < BHT_ENTRIES; i++) {
        uint32_t offset = &area1.entries[BHT_ENTRIES] - &area1.entries[i];
        // uint32_t offset = (BHT_ENTRIES - i);//*4;
        offset <<= 2;
        
        area1.entries[i] = off0_val | encode_branch_offset(offset);
    }
}

//assume training gadget has been written
//init bht with "not taken" condition: "blt a0=2, a1=1, [end]"
void init_nottaken_bht(uint32_t nb_passes) {    

    sig_br* start_branch = (sig_br*)(&area1.entries[0]);

    //take the branches
    for(uint32_t i = 0; i < nb_passes; i++) {
        start_branch(2, 1);
        // return here after all branches from the training gadget have been taken.
        // we do not iterate on the bht entries since all branches instructions in the gadget will be taken successively (condition not met)
    }
}


void touch_taken_bht(uint32_t i) {
    sig_br* touch_branch = (sig_br*) (&area1.entries[i]);
    touch_branch(1, 2);
}

//Alignement is required for precise time measurement: we do not want the fetch to interfere.
__attribute__ ((aligned (I_LINE_SIZE))) __attribute__ ((noinline)) uint32_t poke_taken_bht(uint32_t i) {
    sig_br* touch_branch = (sig_br*) (&area1.entries[i]);
    dummy = ((uint32_t*)touch_branch); // write it somewhere to trigger the addresses computation before the rdtime

    uint32_t start = read_time();
    touch_branch(1, 2);
    uint32_t end = read_time();
    return (end - start);
}

// try to communicate i to spy
volatile void trojan(uint32_t i) {
    uint32_t passes = 1 << BHT_COUNTER_BITS;
    for(uint32_t j = 0; j < passes; j++) {
        touch_taken_bht(i);
    }
}

//try to read o in communication channel
volatile uint32_t spy(uint32_t o) {
    return poke_taken_bht(o);
}

void prepare_trojan() {
    security_domain_switch(0);

    init_nottaken_bht(1 << BHT_COUNTER_BITS);
}

void prepare_spy() {
    security_domain_switch(1);
}

void initialise_benchmark() {
    write_training_gadget();
}

uint32_t get_input_symbols_count() {
    return BHT_ENTRIES;
}

uint32_t get_output_symbols_count() {
    return BHT_ENTRIES;
}