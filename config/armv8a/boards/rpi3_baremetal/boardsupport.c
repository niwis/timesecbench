/*
 * File: boardsupport.c
 * Project: generic
 * Created Date: Wednesday November 4th 2020
 * Author: Ronan (ronan.lashermes@inria.fr)
 * -----
 * Last Modified: Wednesday, 26th May 2021 4:24:08 pm
 * Modified By: Ronan (ronan.lashermes@inria.fr>)
 * -----
 * Copyright (c) 2020 INRIA
 */


#include "support.h"
#include <stdio.h>

FILE *P_FILE;
char* file_name;
int last_o = -1;

void initialise_board (void) {
    file_name = "results.csv";
    P_FILE = fopen(file_name, "w");

    WORD pmcr;
    asm volatile("mrs %0, pmcr_el0" : "=r" (pmcr));
}

volatile void transmit(WORD i, WORD o, WORD timing) {

    if(o != last_o) {
        if(last_o != -1) {
            fprintf(P_FILE, "\n");
        }
        last_o = o;
    }
    if(i == 0) {
        fprintf(P_FILE, "%ld", timing);
    }
    else {
        fprintf(P_FILE, ", %ld", timing);
    }
}

volatile void end_benchmark() {
    fclose(P_FILE);
}
 