/*
 * File: cache.h
 * Project: inc
 * Created Date: Friday July 24th 2020
 * Author: Ronan (ronan.lashermes@inria.fr)
 * -----
 * Last Modified: Monday, 27th July 2020 2:47:50 pm
 * Modified By: Ronan (ronan.lashermes@inria.fr>)
 * -----
 * Copyright (c) 2020 INRIA
 */

#ifndef CACHE_H
#define CACHE_H

#include <stdint.h>




#define DATA_RAM_SIZE 4096
#define INST_RAM_SIZE 4096

#define RAM_SIZE (INST_RAM_SIZE + DATA_RAM_SIZE)

#define D_WAYS 2
// #define D_WAYS 8

#define D_SETS 8
#define D_LINE_SIZE 32
#define L1D_SIZE (D_LINE_SIZE * D_WAYS * D_SETS)
#define L1D_SET_SIZE (D_LINE_SIZE * D_WAYS)

#define D_LAST_LINE_ADD (DATA_RAM_SIZE + INST_RAM_SIZE - D_LINE_SIZE)

void touch_l1d_add(void* address);

//touch and measure time to read
uint32_t poke_l1d_add(void* address);
void prime_l1d();

#endif