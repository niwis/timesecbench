/*
 * File: l1d.c
 * Project: l1d
 * Created Date: Wednesday November 4th 2020
 * Author: Ronan (ronan.lashermes@inria.fr)
 * -----
 * Last Modified: Wednesday, 4th November 2020 4:54:29 pm
 * Modified By: Ronan (ronan.lashermes@inria.fr>)
 * -----
 * Copyright (c) 2020 INRIA
 */


#include "support.h"



volatile uint32_t touch_l1d_add(ADDRESS address) {
    return *address;
}

volatile uint32_t poke_l1d_add(ADDRESS address) {
    uint32_t start = read_time();
    touch_l1d_add(address);
    uint32_t end = read_time();
    return (end - start);
}

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

void prepare_trojan() {

}

void prepare_spy() {
    
}

void initialise_benchmark() {
    
}