/*
 * File: bht.h
 * Project: bht
 * Created Date: Wednesday November 25th 2020
 * Author: Ronan (ronan.lashermes@inria.fr)
 * -----
 * Last Modified: Wednesday, 3rd March 2021 4:30:08 pm
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

typedef unsigned int uint32_t;
typedef void volatile* ADDRESS;
typedef volatile void sig_br(uint32_t rs1, uint32_t rs2);

// A structure of the size the number of bht entries + 1 (for last return instruction) where we can easily write instructions
typedef volatile struct {
    uint32_t entries[BHT_ENTRIES+1];
} __attribute__ ((aligned (256))) //TODO: I get a bug with smaller alignments
bht_work_area;

volatile void write_training_gadget();
volatile void init_nottaken_bht(uint32_t nb_passes);
volatile inline void touch_taken_bht(uint32_t i);
uint32_t poke_taken_bht(uint32_t i);

#endif