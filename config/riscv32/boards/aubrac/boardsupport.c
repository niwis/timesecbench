/*
 * File: boardsupport.c
 * Project: generic
 * Created Date: Wednesday November 4th 2020
 * Author: Ronan (ronan.lashermes@inria.fr)
 * -----
 * Last Modified: Thursday, 5th November 2020 10:24:45 am
 * Modified By: Ronan (ronan.lashermes@inria.fr>)
 * -----
 * Copyright (c) 2020 INRIA
 */

#include "boardsupport.h"
#include "support.h"


void initialise_board (void) {
    
}

volatile void transmit(uint32_t i, uint32_t o, uint32_t timing) {
    //transmission with registers
    __asm__ volatile ("li t6, 0x101010\n"  //trigger signal
                    "mv t5, %[i]\n"
                    "mv t4, %[o]\n"
                    "mv t3, %[timing]\n"
                    : //output
                    : [i] "r" (i), [o] "r" (o), [timing] "r" (timing)//input
                    : "t3", "t4", "t5", "t6"); //cloberred
}