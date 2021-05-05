/*
 * File: boardsupport.c
 * Project: generic
 * Created Date: Wednesday November 4th 2020
 * Author: Ronan (ronan.lashermes@inria.fr)
 * -----
 * Last Modified: Thursday, 26th November 2020 2:12:00 pm
 * Modified By: Ronan (ronan.lashermes@inria.fr>)
 * -----
 * Copyright (c) 2020 INRIA
 */

#include "boardsupport.h"
#include "support.h"
#include <stdio.h>

FILE *P_FILE;
int file_name, C;

void initialise_board (void) {
    file_name="information";
    P_FILE = fopen(file_name, "w");
}

volatile void transmit(uint32_t i, uint32_t o, uint32_t timing) {
    i = 0;
    o = 0;
    timing = 0;
    fprintf(P_FILE, i);
    fprintf(P_FILE, o);
    fprintf(P_FILE, timing);

}

volatile void end_benchmark() {
    fclose(P_FILE);
}