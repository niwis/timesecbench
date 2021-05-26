/*
 * File: btb.h
 * Project: btb
 * Created Date: Thursday November 26th 2020
 * Author: Ronan (ronan.lashermes@inria.fr)
 * -----
 * Last Modified: Wednesday, 26th May 2021 2:38:36 pm
 * Modified By: Ronan (ronan.lashermes@inria.fr>)
 * -----
 * Copyright (c) 2020 INRIA
 */

#ifndef BTB_H
#define BTB_H

#include "support.h"

typedef volatile void sig_jump();

// A structure of the size the number of btb entries + 1 (for last return instruction) where we can easily write instructions
typedef volatile struct {
    uint32_t entries[BTB_ENTRIES+1];
} __attribute__ ((aligned (256))) //TODO: I get a bug with smaller alignments
btb_work_area;

volatile void write_training_gadget();
void init_btb(uint32_t passes);
void touch_one_btb(uint32_t i);
uint32_t poke_one_btb(uint32_t i);

#endif