/*
 * File: main.c
 * Project: src
 * Created Date: Thursday July 9th 2020
 * Author: Ronan (ronan.lashermes@inria.fr)
 * -----
 * Last Modified: Thursday, 30th July 2020 8:57:04 am
 * Modified By: Ronan (ronan.lashermes@inria.fr>)
 * -----
 * Copyright (c) 2020 INRIA
 */

#include "main.h"
#include "boot.h"
#include "gadgets.h"
#include "cache.h"
#include "hsc.h"


// try to communicate i to spy
void trojan(uint32_t i) {
    //touch with 1 < 2
    for(uint32_t j = 0; j < 4; j++) {
        touch_bht(1, 2, i);
    }
}

//try to read o from trojan
uint32_t spy(uint32_t o) {
    //poke with 1 < 2
    return poke_bht(1, 2, o);
}



void main() {

    track2(-2);
    write_training_gadget();
    write_poking_gadget();

    track2(-1);//start signal

    

    for(uint32_t i = 0; i < ALPHABET_SIZE; i++) {
        for(uint32_t o = 0; o < ALPHABET_SIZE; o++) {

            //train with 2 < 1
            init_bht(2, 1, 4, (void*)TRAINING_DATA_ADD); // 1 < 2 (3 passes) -> BRANCH

            hsc_switch_in_place(0, 0x7);
            trojan(i);
            hsc_switch_in_place(1, 0x7);
            uint32_t res = spy(o);

            track(res);
            track2(i*ALPHABET_SIZE + o);
        }
    }
    
    
    track2(0x10000000);//end signal

    infloop();
}



void infloop() {
    while(1) {}
}