/*
 * File: chipsupport.c
 * Project: generic
 * Created Date: Wednesday November 4th 2020
 * Author: Ronan (ronan.lashermes@inria.fr)
 * -----
 * Last Modified: Tuesday, 24th November 2020 3:25:23 pm
 * Modified By: Ronan (ronan.lashermes@inria.fr>)
 * -----
 * Copyright (c) 2020 INRIA
 */

#include "chipsupport.h"

void security_domain_switch(unsigned int domain_id) {
    dome_switch_in_place(domain_id);
}

void instructions_fence(void) {
    asm("fence.i" : : :);
}