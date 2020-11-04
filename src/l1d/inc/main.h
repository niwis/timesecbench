/*
 * File: main.h
 * Project: src
 * Created Date: Thursday July 9th 2020
 * Author: Ronan (ronan.lashermes@inria.fr)
 * -----
 * Last Modified: Monday, 27th July 2020 2:46:49 pm
 * Modified By: Ronan (ronan.lashermes@inria.fr>)
 * -----
 * Copyright (c) 2020 INRIA
 */

#ifndef MAIN_H
#define MAIN_H

#include <stdint.h>

void trojan(uint32_t i);
uint32_t spy(uint32_t o);
void main();
void infloop();

#endif