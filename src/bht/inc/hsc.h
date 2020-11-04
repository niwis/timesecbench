/*
 * File: hsc.h
 * Project: src
 * Created Date: Thursday July 9th 2020
 * Author: Ronan (ronan.lashermes@inria.fr)
 * -----
 * Last Modified: Friday, 24th July 2020 4:17:08 pm
 * Modified By: Ronan (ronan.lashermes@inria.fr>)
 * -----
 * Copyright (c) 2020 INRIA
 */

#ifndef HSC_H
#define HSC_H

#include <stdint.h>

extern void hsc_switch(uint32_t id, void* entry, uint32_t capabilities);
extern void hsc_switch_in_place(uint32_t id, uint32_t capabilities);

#endif