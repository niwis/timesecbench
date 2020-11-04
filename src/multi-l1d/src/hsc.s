/*
 * File: hsc.s
 * Project: src
 * Created Date: Thursday July 9th 2020
 * Author: Ronan (ronan.lashermes@inria.fr)
 * -----
 * Last Modified: Monday, 7th September 2020 9:22:02 am
 * Modified By: Ronan (ronan.lashermes@inria.fr>)
 * -----
 * Copyright (c) 2020 INRIA
 */

# .section .rodata
# dataro0: .word 0x00000018
# dataro1: .word 0x00000088
# dataro2: .word 0x000000ff

.section ".text"

.globl hsc_switch
hsc_switch: #(a0 = id, a1 = hsc entry point, a2 = capabilities)

  csrrw x0, hscworkid, a0
  csrrw x0, hscworkpc, a1
  csrrw x0, hscworkcap, a2

  hscswitch a0
  jr   a1 #in case of no HSC support

.globl hsc_switch_in_place

hsc_switch_in_place:#(a0 = id, ra = hsc entry point, a1 = capabilities)
  csrrw x0, hscworkid, a0
  csrrw x0, hscworkcap, a1
  csrrw x0, hscworkpc, ra

  hscswitch a0
  ret #in case of no HSC support

hsc_start:#(a0 = id, a1 = hsc entry point, a2 = capabilities)
  csrrw x0, hscworkid, a0
  csrrw x0, hscworkpc, a1
  csrrw x0, hscworkcap, a2

  hscstart a0
  jr   a1 #in case of no HSC support

# _hscstart:
#   nop
#   nop
#   nop
#   hscstart x11
#   nop
#   nop
#   nop
#   hscend x12


# end_loop:
#   j end_loop
