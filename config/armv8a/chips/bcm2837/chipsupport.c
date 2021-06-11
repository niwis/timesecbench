/*
 * File: chipsupport.c
 * Project: generic
 * Created Date: Wednesday November 4th 2020
 * Author: Ronan (ronan.lashermes@inria.fr)
 * -----
 * Last Modified: Friday, 11th June 2021 9:39:53 am
 * Modified By: Ronan (ronan.lashermes@inria.fr>)
 * -----
 * Copyright (c) 2020 INRIA
 */

#include "support.h"

void security_domain_switch(WORD domain_id) {
    
}

void instructions_fence(void) {
    __asm__ volatile("dsb sy \n isb" : : : "memory"); 
}

void branch_compare(void) {
    __asm__ volatile("cmp x0, x1" : : : );
}