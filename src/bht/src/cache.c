/*
 * File: cache.c
 * Project: src
 * Created Date: Friday July 24th 2020
 * Author: Ronan (ronan.lashermes@inria.fr)
 * -----
 * Last Modified: Friday, 28th August 2020 11:29:28 am
 * Modified By: Ronan (ronan.lashermes@inria.fr>)
 * -----
 * Copyright (c) 2020 INRIA
 */

#include "cache.h"
#include "gadgets.h"



// uint32_t build_branch_instruction(uint8_t rs1, uint8_t rs2) {
    
// }

// blt a0, a1, 4 -> 0x00B54263

void write_training_gadget() {
    //1 - write branches
    //the branch result (go to next instruction) is the same whether or not the condition (a0 < a1) is taken or not.
    for(uint32_t i = 0; i < BHT_ENTRIES; i++) {
        uint32_t* add = &(((uint32_t*)TRAINING_DATA_ADD)[i]);
        *add = 0xB54263;
    }

    //write ret at the end
    uint32_t* add =  &(((uint32_t*)TRAINING_DATA_ADD)[BHT_ENTRIES]);
    *add = 0x00008067;
}

//assume training gadget has been written
void init_bht(uint32_t rs1, uint32_t rs2, uint32_t nb_passes, void* training_add) {    
    // uint32_t start_train_add = TRAINING_DATA_ADD;

    //2 - take the branches
    for(uint32_t i = 0; i < nb_passes; i++) {
        // asm volatile(   //"li s0, [start_add]\n"
        //                 "mv a0, %[r1]\n"
        //                 "mv a1, %[r2]\n"
        //                 "jalr %[start_add]"
        //                 // "jalr s0"
        //     : [r1] "=r" (rs1), [r2] "=r" (rs2), [start_add] "=A" (training_add)
        //     :
        //     : "a0", "a1", "s0", "ra");
        br_trig(rs1, rs2, training_add);
        

        //return here after branches
    }
    
}

void write_poking_gadget() {
    //write ret at the end
    uint32_t* ret_add = &(((uint32_t*)POKING_DATA_ADD)[BHT_ENTRIES]);
    *ret_add = 0x00008067;
    uint32_t off0_val = 0xB54063;

    for(uint32_t i = 0; i < BHT_ENTRIES; i++) {
        uint32_t* add = &(((uint32_t*)POKING_DATA_ADD)[i]);
        uint32_t offset = ret_add - add;

        //GCC bugfix
        offset <<= 2;
        
        uint32_t final = off0_val;
        final |= (offset >> 4) & 0x80;
        final |= (offset << 7) & 0xF00;
        final |= (offset << 20) & 0x7E000000;
        final |= (offset << 21) & 0x80000000;

        *add = final;
    }
}

void touch_bht(uint32_t rs1, uint32_t rs2, uint32_t i) {
    uint32_t* touch_add = &(((uint32_t*)POKING_DATA_ADD)[i]);
    br_trig(rs1, rs2, (void*) touch_add);
}


uint32_t poke_bht(uint32_t rs1, uint32_t rs2, uint32_t i) {
    
    uint32_t* address = &(((uint32_t*)POKING_DATA_ADD)[i]);
    uint32_t diff;
    asm(    "rdcycle s0\n"
            "jalr   %[add]\n"
            "rdcycle a0\n"
            "sub %[diff], a0, s0\n"

            : [diff] "=r" (diff)// output
            : [add] "r" (address) // input
            : "a0" , "a1", "s0", "ra"      //clobbered
            );
    return diff;
    // uint32_t start = read_time();
    // br_trig(rs1, rs2, (void*)address);
    // uint32_t end = read_time();

    // return end-start;
}
