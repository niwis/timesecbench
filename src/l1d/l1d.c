/*
 * File: l1d.c
 * Project: l1d
 * Created Date: Wednesday November 4th 2020
 * Author: Ronan (ronan.lashermes@inria.fr)
 * -----
 * Last Modified: Wednesday, 26th May 2021 3:47:42 pm
 * Modified By: Ronan (ronan.lashermes@inria.fr>)
 * -----
 * Copyright (c) 2020 INRIA
 */

#include "support.h"
#include "l1d.h"

l1d_work_area area1;
l1d_work_area area2;


WORD touch_l1d_add(ADDRESS address) {
    return  *((WORD volatile*)address);
}


//Alignement is required for precise time measurement: we do not want the fetch to interfere.
__attribute__ ((aligned (I_LINE_SIZE))) __attribute__ ((noinline)) volatile TIMECOUNT poke_l1d_add(ADDRESS address) {
    TIMECOUNT start = read_time();
    touch_l1d_add(address);
    TIMECOUNT end = read_time();
    return (end - start);
}

// try to communicate i to spy
volatile void trojan(WORD i) {
    //here i is set index
    touch_l1d_add((void *) ((WORD)(&area2) + i*D_LINE_SIZE ) );
}

//try to read o in communication channel
volatile TIMECOUNT spy(WORD o) {
    //here o is a set index
    // return poke_l1d_add((void *) ((WORD)(&area2) + o*D_LINE_SIZE) );
    TIMECOUNT v = poke_l1d_add((void *) ((WORD)(&area2) + o*D_LINE_SIZE) );
    return v;
}

void prepare_trojan() {
    security_domain_switch(0);


    // to prepare trojan, we must touch memory someplaces never touched by trojan as to fill the cache
    for (WORD w = 0; w < D_WAYS; w++) {
        for (WORD s = 0; s < D_SETS; s++) {
            // touch_l1d_add((void*)(D_LAST_LINE - s - w*D_SETS));
            
            touch_l1d_add((void*)((WORD)(&area1) + D_LINE_SIZE * (s + w*D_SETS)));
        }
    }
}

void prepare_spy() {
    security_domain_switch(1);
}

void initialise_benchmark() {
    
}

WORD get_input_symbols_count() {
    return D_SETS;
}

WORD get_output_symbols_count() {
    return D_SETS;
}