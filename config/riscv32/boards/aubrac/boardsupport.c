/*
 * File: boardsupport.c
 * Project: generic
 * Created Date: Wednesday November 4th 2020
 * Author: Ronan (ronan.lashermes@inria.fr)
 * -----
 * Last Modified: Wednesday, 4th November 2020 5:09:25 pm
 * Modified By: Ronan (ronan.lashermes@inria.fr>)
 * -----
 * Copyright (c) 2020 INRIA
 */

#include "boardsupport.h"

typedef unsigned int uint32_t;

volatile uint32_t read_time() {
    uint32_t time;
    __asm__ volatile ("rdcycle %[time]" : [time] "=r" (time) : : );
    return time;
}

volatile void transmit(uint32_t i, uint32_t o, uint32_t timing) {
    //transmission with registers
    __asm__ volatile ("li x31, 0x101010\n"  //trigger signal
                    "mv x30, %[i]\n"
                    "mv x29, %[o]\n"
                    "mv x28, %[timing]\n"
                    : //output
                    : [i] "r" (i), [o] "r" (o), [timing] "r" (timing)//input
                    : "memory"); //cloberred
}