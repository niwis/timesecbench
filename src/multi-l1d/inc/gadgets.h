/*
 * File: gadgets.h
 * Project: inc
 * Created Date: Tuesday July 21st 2020
 * Author: Ronan (ronan.lashermes@inria.fr)
 * -----
 * Last Modified: Monday, 31st August 2020 10:18:16 am
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
extern volatile uint32_t get_hart_id();
extern volatile void wait_for_spy_sync_loop();
extern volatile void wait_for_trojan_sync_loop();

#endif /* GADGETS_H */