/*
 * File: main.c
 * Project: src
 * Created Date: Thursday July 9th 2020
 * Author: Ronan (ronan.lashermes@inria.fr)
 * -----
 * Last Modified: Monday, 27th July 2020 3:01:25 pm
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
    touch_l1d_add((void *) (i*D_LINE_SIZE ) );
}

//try to read o in communication channel
uint32_t spy(uint32_t o) {
    //here o is a set index
    return poke_l1d_add((void *) (o*D_LINE_SIZE) );
}


void main() {
    track2(-1);//start signal

    

    for(uint32_t i = 0; i < D_SETS; i++) {
        for(uint32_t o = 0; o < D_SETS; o++) {
            prime_l1d();

            hsc_switch_in_place(0, 0x7);
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