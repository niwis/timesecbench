/*
 * File: chipsupport.c
 * Project: generic
 * Created Date: Wednesday November 4th 2020
 * Author: Ronan (ronan.lashermes@inria.fr)
 * -----
 * Last Modified: Wednesday, 25th November 2020 3:21:52 pm
 * Modified By: Ronan (ronan.lashermes@inria.fr>)
 * -----
 * Copyright (c) 2020 INRIA
 */

#include "chipsupport.h"

void security_domain_switch(unsigned int domain_id) {
    
}

void instructions_fence(void) {
    // asm("fence.i" : : : "memory"); 
}