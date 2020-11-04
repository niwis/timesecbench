/*
 * File: main.c
 * Project: src
 * Created Date: Thursday July 9th 2020
 * Author: Ronan (ronan.lashermes@inria.fr)
 * -----
 * Last Modified: Tuesday, 28th July 2020 2:51:28 pm
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
    //here i is set index
    touch_l1i_add((void *) (i * I_LINE_SIZE) );
}

//try to read o in communication channel
uint32_t spy(uint32_t o) {
    //here o is a set index
    return poke_l1i_add((void *) (o * I_LINE_SIZE) );
}

//write the "ret" instructions where we will touch or poke them
void prepare() {
    for(uint32_t s = 0; s < I_SETS; s++) {
        uint32_t add = s * I_LINE_SIZE;
        write_u32((void *) add, 0x00008067);
    }
}

void main() {

    track2(-2);//start signal
    prepare();
    track2(-1);//start signal

    

    for(uint32_t i = 0; i < D_SETS; i++) {
        for(uint32_t o = 0; o < D_SETS; o++) {
            

            hsc_switch_in_place(0, 0x7);
            prime_l1i();
            trojan(i);
            hsc_switch_in_place(1, 0x7);
            uint32_t res = spy(o);

            track(res);
            track2(i*D_SETS + o);
        }
    }
    
    
    track2(0x10000000);//end signal

    infloop();
}



void infloop() {
    while(1) {}
}