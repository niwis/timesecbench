/*
 * File: boardsupport.c
 * Project: generic
 * Created Date: Wednesday November 4th 2020
 * Author: Ronan (ronan.lashermes@inria.fr)
 * -----
 * Last Modified: Friday, 27th August 2021 4:34:26 pm
 * Modified By: Ronan (ronan.lashermes@inria.fr>)
 * -----
 * Copyright (c) 2020 INRIA
 */


#include "support.h"
#include "../../../../../common/include/uart.h"
#include <string.h>


#define ARMV8_PMCR_MASK         0x3f
#define ARMV8_PMCR_E            (1 << 0) /*  Enable all counters */
#define ARMV8_PMCR_P            (1 << 1) /*  Reset all counters */
#define ARMV8_PMCR_C            (1 << 2) /*  Cycle counter reset */
#define ARMV8_PMCR_D            (1 << 3) /*  Enable divider by 64 */
#define ARMV8_PMCR_N_MASK       0x1f

#define ARMV8_PMUSERENR_EN_EL0  (1 << 0) /*  EL0 access enable */
#define ARMV8_PMUSERENR_CR      (1 << 2) /*  Cycle counter read enable */
#define ARMV8_PMUSERENR_ER      (1 << 3) /*  Event counter read enable */

#define ARMV8_PMCNTENSET_EL0_ENABLE (1<<31) /* *< Enable Perf count reg */

#define PERF_DEF_OPTS (1 | 16)

char transmit_text[50];

static void disable_prefetch(void)
{
    unsigned long value = 0;
    asm volatile("mrs %0, S3_1_C15_C2_0" : "=r" (value)); // read register
    asm volatile("msr S3_1_C15_C2_0, %0" :: "r" (value)); // write register

}


void initialise_board (void) {
    disable_prefetch();
    /*Enable user-mode access to counters. */
    asm volatile("msr pmuserenr_el0, %0" : : "r"((u64)ARMV8_PMUSERENR_EN_EL0|ARMV8_PMUSERENR_ER|ARMV8_PMUSERENR_CR));

    /*   Performance Monitors Count Enable Set register bit 30:0 disable, 31 enable. Can also enable other event counters here. */ 
    asm volatile("msr pmcntenset_el0, %0" : : "r" (ARMV8_PMCNTENSET_EL0_ENABLE));

    /* Enable counters */
    unsigned long val=0;
    asm volatile("mrs %0, pmcr_el0" : "=r" (val));
    asm volatile("msr pmcr_el0, %0" : : "r" (val|(ARMV8_PMCR_E & (~ARMV8_PMCR_D))));

    WORD pmcr;
    asm volatile("mrs %0, pmcr_el0" : "=r" (pmcr));

    // sprintf(transmit_text, "pmcr=%lx\n\r", pmcr);
    // uart_print(transmit_text);
}

volatile TIMECOUNT read_time() 
{
    TIMECOUNT r;
    /* Access cycle counter */
    __asm__ volatile("mrs %0, pmccntr_el0" : "=r" (r));
    // __asm__ volatile("mrs %0, pmccntr" : "=r" (r));

    return r;
}

void transmit(WORD i, WORD o, WORD timing) {
    sprintf(transmit_text, "%ld, %ld, %ld\n", i, o, timing);
    uart_print(transmit_text);
}

void end_benchmark() {
    sprintf(transmit_text, "ack\n");
    uart_print(transmit_text);
}
 