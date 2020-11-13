/*
 * File: l1d.c
 * Project: l1d
 * Created Date: Wednesday November 4th 2020
 * Author: Ronan (ronan.lashermes@inria.fr)
 * -----
 * Last Modified: Friday, 13th November 2020 2:41:11 pm
 * Modified By: Ronan (ronan.lashermes@inria.fr>)
 * -----
 * Copyright (c) 2020 INRIA
 */


#include "support.h"
#include "l1d.h"


uint32_t touch_l1d_add(ADDRESS address) {
    return  *((uint32_t volatile*)address);
}



__attribute__ ((aligned (I_LINE_SIZE))) __attribute__ ((noinline)) volatile uint32_t poke_l1d_add(ADDRESS address) {
    uint32_t start = read_time();
    touch_l1d_add(address);
    uint32_t end = read_time();
    return (end - start);
}

// try to communicate i to spy
volatile void trojan(uint32_t i) {
    //here i is set index
    touch_l1d_add((void *) (i*D_LINE_SIZE ) );
}

//try to read o in communication channel
volatile uint32_t spy(uint32_t o) {
    //here o is a set index
    return poke_l1d_add((void *) (o*D_LINE_SIZE) );
}

void prepare_trojan() {
    security_domain_switch(0);

    uint32_t start_add = D_SETS * D_WAYS;

    // to prepare trojan, we must touch memory someplaces never touched by trojan as to fill the cache
    for (uint32_t w = 0; w < D_WAYS; w++) {
        for (uint32_t s = 0; s < D_SETS; s++) {
            // touch_l1d_add((void*)(D_LAST_LINE - s - w*D_SETS));
            touch_l1d_add((void*)(D_LINE_SIZE * (start_add + s + w*D_SETS)));
        }
    }
}

void prepare_spy() {
    security_domain_switch(1);
}

void initialise_benchmark() {
    
}

uint32_t get_input_symbols_count() {
    return D_SETS;
}

uint32_t get_output_symbols_count() {
    return D_SETS;
}