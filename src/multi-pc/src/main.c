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

#define TROJAN_IT 50
#define SPY_IT 150


// try to communicate i to spy
void trojan(uint32_t i) {
    //here i is set index
    



    if (i%2 == 0) {

        uint32_t temp = 2;
        uint32_t op = 3;
        for(uint32_t n = 0; n < TROJAN_IT; n++) {
            asm("mul %[temp], %[temp], %[op]\n"
                : //[temp] "=r" (temp)// output
                : [op] "r" (op), [temp] "r" (temp) // input
                :     //clobbered
                );
        }
    }
    else {
        uint32_t temp = 2;
        uint32_t op = 3;
        for(uint32_t n = 0; n < TROJAN_IT; n++) {
            asm("add %[temp], %[temp], %[temp]\n"
                "add %[temp], %[temp], %[temp]\n"
                "add %[temp], %[temp], %[temp]\n"
                "add %[temp], %[temp], %[temp]\n"
                "add %[temp], %[temp], %[temp]\n"
                "add %[temp], %[temp], %[temp]\n"
                : //[temp] "=r" (temp)// output
                : [temp] "r" (temp) // input
                :     //clobbered
                );
        }
    }
    
}

//try to read o in communication channel
uint32_t spy(uint32_t o) {
    uint32_t start = read_time();

    if (o%2 == 0) {
        uint32_t temp = 2;
        uint32_t op = 3;
        for(uint32_t n = 0; n < TROJAN_IT; n++) {
            asm("mul %[temp], %[temp], %[op]\n"
                : //[temp] "=r" (temp)// output
                : [op] "r" (op), [temp] "r" (temp) // input
                :     //clobbered
                );
        }
    }
    else {
        uint32_t temp = 2;
        uint32_t op = 3;
        for(uint32_t n = 0; n < TROJAN_IT; n++) {
            asm("add %[temp], %[temp], %[temp]\n"
                "add %[temp], %[temp], %[temp]\n"
                "add %[temp], %[temp], %[temp]\n"
                "add %[temp], %[temp], %[temp]\n"
                "add %[temp], %[temp], %[temp]\n"
                "add %[temp], %[temp], %[temp]\n"
                : //[temp] "=r" (temp)// output
                : [temp] "r" (temp) // input
                :     //clobbered
                );
        }
    }

    uint32_t stop = read_time();
    return stop - start;
}


//core 0 is trojan
void main_trojan() {
    track2(-1);//start signal
    hsc_switch_in_place(0, 0x4);

    wait_for_spy_sync();

    for(uint32_t i = 0; i < SYMBOLS_COUNT; i++) {
        for(uint32_t o = 0; o < SYMBOLS_COUNT; o++) {

            trojan_sync();
            wait_for_spy_sync();

            trojan(i);
            track2(i*SYMBOLS_COUNT + o);

        }
    }


    track2(0x10000000);//end signal

    infloop();
}

//core 1 is spy
void main_spy() {
    track2(-1);//start signal
    hsc_switch_in_place(1, 0x4);

    spy_sync();

    for(uint32_t i = 0; i < SYMBOLS_COUNT; i++) {
        for(uint32_t o = 0; o < SYMBOLS_COUNT; o++) {

            wait_for_trojan_sync();
            spy_sync();

            uint32_t res = spy(o);
            track(res);
            track2(i*SYMBOLS_COUNT + o);

            
        }
    }


    track2(0x10000000);//end signal

    infloop();
}



void infloop() {
    while(1) {}
}
