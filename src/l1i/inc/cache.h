/*
 * File: cache.h
 * Project: inc
 * Created Date: Friday July 24th 2020
 * Author: Ronan (ronan.lashermes@inria.fr)
 * -----
 * Last Modified: Tuesday, 28th July 2020 2:28:54 pm
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
#define D_SETS 8
#define D_LINE_SIZE 32

#define L1D_SIZE (D_LINE_SIZE * D_WAYS * D_SETS)
#define L1D_SET_SIZE (D_LINE_SIZE * D_WAYS)

#define I_WAYS 2
#define I_SETS 8
#define I_LINE_SIZE 64

#define L1I_SIZE (I_LINE_SIZE * I_WAYS * I_SETS)
#define L1I_SET_SIZE (I_LINE_SIZE * I_WAYS)

#define I_LAST_LINE_ADD (DATA_RAM_SIZE + INST_RAM_SIZE - I_LINE_SIZE)
#define D_LAST_LINE_ADD (DATA_RAM_SIZE + INST_RAM_SIZE - D_LINE_SIZE)

void prime_l1i();
void touch_l1d_add(void* address);

//touch and measure time to read
uint32_t poke_l1d_add(void* address);

void touch_l1i_add(void *address);
uint32_t poke_l1i_add(void (*address)());
void prime_l1d();

#endif