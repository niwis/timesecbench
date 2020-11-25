/*
 * File: bht.h
 * Project: bht
 * Created Date: Wednesday November 25th 2020
 * Author: Ronan (ronan.lashermes@inria.fr)
 * -----
 * Last Modified: Wednesday, 25th November 2020 3:33:05 pm
 * Modified By: Ronan (ronan.lashermes@inria.fr>)
 * -----
 * Copyright (c) 2020 INRIA
 */

#ifndef BHT_H
#define BHT_H

// requires
// - BLT01_OPCODE
// - RET_OPCODE
// - BHT_ENTRIES
// - I_LINE_SIZE
// - WORK_ADD1
// - WORK_ADD2

typedef unsigned int uint32_t;
typedef void volatile* ADDRESS;
typedef volatile void sig_br(uint32_t rs1, uint32_t rs2);

volatile void write_training_gadget();
volatile void write_poking_gadget();
volatile void init_nottaken_bht(uint32_t nb_passes);
volatile inline void touch_taken_bht(uint32_t i);
uint32_t poke_taken_bht(uint32_t i);

#endif