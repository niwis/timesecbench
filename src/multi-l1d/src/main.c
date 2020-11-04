/*
 * File: main.c
 * Project: src
 * Created Date: Thursday July 9th 2020
 * Author: Ronan (ronan.lashermes@inria.fr)
 * -----
 * Last Modified: Monday, 7th September 2020 8:49:06 am
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


//core 0 is trojan
void main_trojan() {
    track2(-1);//start signal
    hsc_switch_in_place(0, 0x0);

    for(uint32_t i = 0; i < D_SETS; i++) {
        for(uint32_t o = 0; o < D_SETS; o++) {

            wait_for_spy_sync();

            prime_l1d();
            trojan(i);

            track2(i*D_SETS + o);

            trojan_sync();
        }
    }


    track2(0x10000000);//end signal

    infloop();
}

//core 1 is spy
void main_spy() {
    track2(-1);//start signal
    hsc_switch_in_place(1, 0x0);
    prime_l1d();
    spy_sync();

    for(uint32_t i = 0; i < D_SETS; i++) {
        for(uint32_t o = 0; o < D_SETS; o++) {

            wait_for_trojan_sync();

            uint32_t res = spy(o);
            track(res);

            track2(i*D_SETS + o);
            prime_l1d();
            spy_sync();
        }
    }


    track2(0x10000000);//end signal

    infloop();
}



void infloop() {
    while(1) {}
}
