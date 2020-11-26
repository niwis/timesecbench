/*
 * File: btb.h
 * Project: btb
 * Created Date: Thursday November 26th 2020
 * Author: Ronan (ronan.lashermes@inria.fr)
 * -----
 * Last Modified: Thursday, 26th November 2020 2:01:22 pm
 * Modified By: Ronan (ronan.lashermes@inria.fr>)
 * -----
 * Copyright (c) 2020 INRIA
 */

#ifndef BTB_H
#define BTB_H

typedef volatile void sig_jump();
typedef unsigned int uint32_t;
typedef void volatile* ADDRESS;

volatile void write_training_gadget();
void init_btb(uint32_t passes);
void touch_one_btb(uint32_t i);
uint32_t poke_one_btb(uint32_t i);

#endif