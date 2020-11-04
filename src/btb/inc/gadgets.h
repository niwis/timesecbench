/*
 * File: gadgets.h
 * Project: inc
 * Created Date: Tuesday July 21st 2020
 * Author: Ronan (ronan.lashermes@inria.fr)
 * -----
 * Last Modified: Tuesday, 25th August 2020 4:45:43 pm
 * Modified By: Ronan (ronan.lashermes@inria.fr>)
 * -----
 * Copyright (c) 2020 INRIA
 */

#ifndef GADGETS_H
#define GADGETS_H

#include <stdint.h>

extern volatile uint32_t read_u32(void* add);
extern volatile uint32_t write_u32(void* add, uint32_t val);
extern volatile uint32_t read_time();
extern volatile uint32_t track(uint32_t val);
extern volatile uint32_t track2(uint32_t val);
extern volatile void br_trig(uint32_t rs1, uint32_t rs2, void* table_add);
extern volatile uint32_t training_btb();
extern volatile uint32_t ret_zero();
extern volatile uint32_t ret_one();


#endif /* GADGETS_H */