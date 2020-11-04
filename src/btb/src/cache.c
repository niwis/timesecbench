/*
 * File: cache.c
 * Project: src
 * Created Date: Friday July 24th 2020
 * Author: Ronan (ronan.lashermes@inria.fr)
 * -----
 * Last Modified: Thursday, 27th August 2020 10:39:30 am
 * Modified By: Ronan (ronan.lashermes@inria.fr>)
 * -----
 * Copyright (c) 2020 INRIA
 */

#include "cache.h"
#include "gadgets.h"

uint32_t zero_jumps[BTB_ENTRIES];
uint32_t one_jumps[BTB_ENTRIES];

uint32_t gen_jump(uint32_t offset) {

    uint32_t imm = offset & 0xFF000;
    imm |= (offset << 11) & 0x80000000;
    imm |= (offset << 20) & 0x7FE00000;
    imm |= (offset << 9) & 0x00100000;

    return 0x6F | imm;
}

void generate_all_jumps() {
    //generate jumps
    for (uint32_t i = 0; i < BTB_ENTRIES; i++)
    {
        uint32_t* callsite = (uint32_t*) &(((uint32_t*)training_btb)[i]);
        uint32_t ret_zero_add = ((uint32_t) ret_zero);
        uint32_t ret_one_add = ((uint32_t) ret_one);
        zero_jumps[i] = gen_jump(ret_zero_add - (uint32_t) callsite);
        one_jumps[i] = gen_jump(ret_one_add - (uint32_t) callsite);
    }
}

//assume training gadget has been written
void init_btb(uint32_t nb_passes) {    

    //1 - rewrite "j ret_zero" everywhere
    for(uint32_t i = 0; i < BTB_ENTRIES; i++) {
        uint32_t* callsite = (uint32_t*) &(((uint32_t*)training_btb)[i]);
;
        *callsite = zero_jumps[i];
    }

    // 2 - train
    for(uint32_t p = 0; p < nb_passes; p++) {

        for(uint32_t i = 0; i < BTB_ENTRIES; i++) {
            void (*callsite)() = (void (*)())  &(((uint32_t*)training_btb)[i]);
;
            (*callsite)();
        }

    }
    
}


void touch_btb(uint32_t i) {
    volatile uint32_t* touch_add = &(((uint32_t*)training_btb)[i]);

    //1 - rewrite "j ret_one"
    *touch_add = one_jumps[i];

    asm ( "jalr %[add]\n"
        :
        : [add] "r" (touch_add)
        : "ra", "a0"
        );

    //2 - rewrite "j ret_zero"
    *touch_add = zero_jumps[i];
}


uint32_t poke_btb(uint32_t i) {
    
    // volatile uint32_t* address = (uint32_t*)((uint32_t)training_btb) + (i << 2);
    volatile uint32_t* address = &(((uint32_t*)training_btb)[i]);

    //1 - rewrite "j ret_one"
    *address = one_jumps[i];

    //2 - measure time
    uint32_t diff;
    asm(    "rdcycle s0\n"
            "jalr   %[add]\n"
            "rdcycle a0\n"
            "sub %[diff], a0, s0\n"

            : [diff] "=r" (diff)// output
            : [add] "r" (address) // input
            : "a0" , "a1", "s0", "ra"      //clobbered
            );
        
    //3 - rewrite "j ret_zero"
    *address = zero_jumps[i];

    return diff;
    // uint32_t start = read_time();
    // br_trig(rs1, rs2, (void*)address);
    // uint32_t end = read_time();

    // return end-start;
}
