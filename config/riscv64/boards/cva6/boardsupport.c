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
#include "uart.h"
#include "printf.h"
// #include <string.h>

char transmit_text[50];

void initialise_board (void) {
    init_uart(50000000, 115200);
    print_uart("Init board\r\n");
    // Set CSR so we can use rdcycle from M mode.
    __asm__ volatile("csrwi 0x306, 0xf");
    // Enable L2 performance counters
    volatile uint64_t *L2_performance_counters_enable = ((volatile uint64_t*)L2_REG_PCNT_CFG);
    *L2_performance_counters_enable = 1;
}

volatile void transmit(WORD i, WORD o, WORD timing) {
    //Transmission through UART
    sprintf(transmit_text, "%lu,%lu,%lu\r\n", i, o, timing);
    print_uart(transmit_text);
}

volatile void end_benchmark() {
    print_uart("End of benchmark\r\n");
}