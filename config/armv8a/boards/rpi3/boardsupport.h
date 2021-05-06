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
#include <time.h>
#include <stdio.h>

#define CPU_MHZ 1
typedef unsigned int uint32_t;

volatile inline uint32_t read_time() {
    struct timespec stop;
    struct timespec start;
    float exec_time;
    uint32_t time;
    clock_gettime(CLOCK_MONOTONIC, &start); 
    const clock_t start_tick = clock(); 
    clock_t current_tick = clock();
    clock_gettime(CLOCK_MONOTONIC, &stop); 
    printf("II. Current tick - start to: %u\n", (unsigned int)(current_tick-start_tick));
    exec_time = ( stop.tv_sec - start.tv_sec ) + ( stop.tv_nsec - start.tv_nsec ) / 1000000000.0;
    printf("II. Sleep took time: %f\n", exec_time);
    // __asm__ volatile ("rdcycle %[time]" : [time] "=r" (time) : : );
    return time;
}


#endif