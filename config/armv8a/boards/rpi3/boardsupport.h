/*
 * File: boardsupport.h
 * Project: generic
 * Created Date: Wednesday November 4th 2020
 * Author: Ronan (ronan.lashermes@inria.fr)
 * -----
 * Last Modified: Friday, 6th November 2020 10:36:23 am
 * Modified By: Ronan (ronan.lashermes@inria.fr>)
 * -----
 * Copyright (c) 2020 INRIA
 */

#ifndef BOARDSUPPORT_H
#define BOARDSUPPORT_H

#define CPU_MHZ 1
long int start_time;
long int time_difference;
typedef unsigned int uint32_t;

volatile inline uint32_t read_time() {
    uint32_t time;
    clock_gettime();
    // __asm__ volatile ("rdcycle %[time]" : [time] "=r" (time) : : );
    return time;
}


#endif