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

readticks(unsigned int *result, int enabled)
{
    struct timeval t;
    unsigned int cc;
    unsigned int val;
    if (!enabled) {
        // program the performance-counter control-register:
        asm volatile("msr pmcr_el0, %0" : : "r" (17));
        //enable all counters
        asm volatile("msr PMCNTENSET_EL0, %0" : : "r" (0x8000000f));
        //clear the overflow 
        asm volatile("msr PMOVSCLR_EL0, %0" : : "r" (0x8000000f));
        enabled = 1;
    }
    //read the coutner value
    asm volatile("mrs %0, PMCCNTR_EL0" : "=r" (cc));
    gettimeofday(&t,(struct timezone *) 0);
    result[0] = cc;
    result[1] = t.tv_usec;
    result[2] = t.tv_sec;

volatile inline uint32_t read_time() {
    unsigned int init[3] = {0};
    unsigned int start[3] = {0};
    unsigned int end[3] = {0};
    unsigned int overhead = 0;

    readticks(init, 0);
    readticks(start, 1);
    readticks(end, 1);

    overhead = end[0] - start[0];
    readticks(init, 0);
    readticks(start, 1);
    foo(); //This is my function 
    readticks(end, 1);

    end[0] = end[0] - start[0] - overhead;
    printf("clock cycles= %d\n", end[0]);
    return 0;
return time;
}


#endif