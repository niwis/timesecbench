/*
 * File: cache.h
 * Project: inc
 * Created Date: Friday July 24th 2020
 * Author: Ronan (ronan.lashermes@inria.fr)
 * -----
 * Last Modified: Thursday, 27th August 2020 11:47:23 am
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

#define BHT_ENTRIES 128
#define BHT_SETS    8
#define BHT_COUNTER_BITS    2

#define BTB_ENTRIES 16

#define TRAINING_DATA_ADD 0x1400
#define POKING_DATA_ADD 0x1800 // > TRAINING_DATA_ADD + 8 * BHT_ENTRIES + Return gadget + 7 bit align

#define ALPHABET_SIZE 16

void write_training_gadget();
void write_poking_gadget();

void generate_all_jumps();
void init_btb(uint32_t nb_passes);
void touch_btb(uint32_t i);
uint32_t poke_btb(uint32_t i);

#endif