/*
 * File: boot.s
 * Project: src
 * Created Date: Thursday July 9th 2020
 * Author: Ronan (ronan.lashermes@inria.fr)
 * -----
 * Last Modified: Monday, 7th September 2020 10:19:35 am
 * Modified By: Ronan (ronan.lashermes@inria.fr>)
 * -----
 * Copyright (c) 2020 INRIA
 */

.section ".data"
    .word 0x00001000

.section ".boot"

.globl _start
_start:
    csrrs t0, mhartid, x0 #read current hart id

    bne t0, x0, hart_spy#branch to not_zero if hart id is not zero, if hsc is enabled, we start with only one hart

#trojan (hsc 0)
#jump to zero in in context
pretrojan:
    la a0, prespy
    li a1, 0x0

    csrrw x0, hscworkid, x0
    csrrw x0, hscworkpc, a0
    csrrw x0, hscworkcap, a1
    hscswitch a0
    jr a0

prespy:
    li a0, 1 #hsc id
    la a1, hart_spy
    li a2, 0x0

    csrrw x0, hscworkid, a0
    csrrw x0, hscworkpc, a1
    csrrw x0, hscworkcap, a2
    hscstart a0

hart_trojan:
    li sp, 0xFFF
    j main_trojan

    
hart_spy:
    li sp, 0x7FF
    j main_spy
    