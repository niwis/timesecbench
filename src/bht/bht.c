/*
 * File: bht.c
 * Project: bht
 * Created Date: Wednesday November 25th 2020
 * Author: Ronan (ronan.lashermes@inria.fr)
 * -----
 * Last Modified: Friday, 11th June 2021 9:36:52 am
 * Modified By: Ronan (ronan.lashermes@inria.fr>)
 * -----
 * Copyright (c) 2020 INRIA
 */

#include "support.h"
#include "bht.h"

bht_work_area area1;
volatile WORD* dummy;

// the gadget is an array of "blt a0, a1, [gadget_end]" (size = BHT_ENTRIES), terminating with a ret
// if we execute one instruction, it will be the only branch to be taken if the condition is met, or all successive branches will be taken if not met.
void write_gadget() {
    //write ret at the end
    area1.entries[BHT_ENTRIES] = RET_OPCODE;
    uint32_t off0_val = BLT01_OPCODE;

    for(uint32_t i = 0; i < BHT_ENTRIES; i++) {
        uint32_t offset = &area1.entries[BHT_ENTRIES] - &area1.entries[i];
        // offset <<= 2;
        
        area1.entries[i] = off0_val | encode_branch_offset(offset);
    
    }
    
}

//assume gadget has been written
//init bht with "not taken" condition: "blt a0=2, a1=1, [end]"
void init_nottaken_bht(WORD nb_passes) {    
    sig_br* start_branch = (sig_br*)(&area1.entries[0]);
    //take the branches
    for(WORD i = 0; i < nb_passes; i++) {
        branch_compare();
        start_branch(2, 1);
        // return here after all branches from the training gadget have been taken.
        // we do not iterate on the bht entries since all branches instructions in the gadget will be taken successively (condition not met)
    }
}


void touch_taken_bht(WORD i) {
    sig_br* touch_branch = (sig_br*) (&area1.entries[i]);
    branch_compare();
    touch_branch(1, 2);
}

//Alignement is required for precise time measurement: we do not want the fetch to interfere.
__attribute__ ((aligned (I_LINE_SIZE))) __attribute__ ((noinline)) TIMECOUNT poke_taken_bht(WORD i) {
    sig_br* touch_branch = (sig_br*) (&area1.entries[i]);
    dummy = ((WORD*)touch_branch); // write it somewhere to trigger the addresses computation before the rdtime
    branch_compare();
    TIMECOUNT start = read_time();
    touch_branch(1, 2);
    TIMECOUNT end = read_time();
    return (end - start);
}

// try to communicate i to spy
void trojan(WORD i) {
    WORD passes = 1 << BHT_COUNTER_BITS;
    for(WORD j = 0; j < passes; j++) {
        touch_taken_bht(i);
    }
}

//try to read o in communication channel
TIMECOUNT spy(WORD o) {
    return poke_taken_bht(o);
}

void prepare_trojan() {
    security_domain_switch(0);

    init_nottaken_bht(1 << BHT_COUNTER_BITS);
}

void prepare_spy() {
    security_domain_switch(1);
    asm volatile (".word 0xfffff00b"); // fence.t
}

void initialise_benchmark() {
    write_gadget();
}

WORD get_input_symbols_count() {
    return BHT_ENTRIES;
}

WORD get_output_symbols_count() {
    return BHT_ENTRIES;
}