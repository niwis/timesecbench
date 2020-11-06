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
typedef unsigned int uint32_t;

volatile inline uint32_t read_time() {
    uint32_t time;
    __asm__ volatile ("rdcycle %[time]" : [time] "=r" (time) : : );
    return time;
}

extern void dome_switch_in_place(unsigned int domain_id);

#endif