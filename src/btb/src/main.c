/*
 * File: main.c
 * Project: src
 * Created Date: Thursday July 9th 2020
 * Author: Ronan (ronan.lashermes@inria.fr)
 * -----
 * Last Modified: Thursday, 27th August 2020 10:39:52 am
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
    // for(uint32_t j = 0; j < 4; j++) {
        touch_btb(i);
    // }
}

//try to read o from trojan
uint32_t spy(uint32_t o) {
    return poke_btb(o);
}



void main() {

    generate_all_jumps();
    track2(-1);//start signal

    for(uint32_t i = 0; i < ALPHABET_SIZE; i++) {
        for(uint32_t o = 0; o < ALPHABET_SIZE; o++) {

            init_btb(2);

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