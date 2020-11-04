/*
 * File: boot.s
 * Project: src
 * Created Date: Thursday July 9th 2020
 * Author: Ronan (ronan.lashermes@inria.fr)
 * -----
 * Last Modified: Tuesday, 21st July 2020 3:05:44 pm
 * Modified By: Ronan (ronan.lashermes@inria.fr>)
 * -----
 * Copyright (c) 2020 INRIA
 */

.section ".data"
    .word 0x00001000

.section ".boot"

.globl _start
_start:
    li sp, 0xFFF
    j main
    