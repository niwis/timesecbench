/*
 * File: boardsupport.h
 * Project: generic
 * Created Date: Wednesday November 4th 2020
 * Author: Ronan (ronan.lashermes@inria.fr)
 * -----
 * Last Modified: Friday, 11th June 2021 9:40:00 am
 * Modified By: Ronan (ronan.lashermes@inria.fr>)
 * -----
 * Copyright (c) 2020 INRIA
 */

#ifndef BOARDSUPPORT_H
#define BOARDSUPPORT_H
#include <time.h>
#include <stdio.h>
#include <sys/time.h>
#include "../../armv8a.h"

#define CPU_MHZ 1




volatile inline TIMECOUNT read_time() 
{
    TIMECOUNT r;
    /* Access cycle counter */
    __asm__ volatile("mrs %0, pmccntr_el0" : "=r" (r));

    return r;
}
#endif