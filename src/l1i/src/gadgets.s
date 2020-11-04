/*
 * File: gadgets.s
 * Project: src
 * Created Date: Tuesday July 21st 2020
 * Author: Ronan (ronan.lashermes@inria.fr)
 * -----
 * Last Modified: Tuesday, 28th July 2020 11:25:48 am
 * Modified By: Ronan (ronan.lashermes@inria.fr>)
 * -----
 * Copyright (c) 2020 INRIA
 */

.section ".text"

.globl read_u32
read_u32:
    lw  a0, 0(a0)
    ret

.globl write_u32
write_u32:
    sw a1, 0(a0)
    ret
    
.globl read_time
read_time:
    rdcycle a0
    ret

# touch a rarely used register (x28) to track a value in the hardware simulation
.globl track
track:
    mv x28, a0
    ret

    
.globl track2
track2:
    mv x29, a0
    ret
    
# .globl poke_l1d_add
# poke_l1d_add:
#     # save s0
#     addi	sp,sp,-4
#     sw	    s0,0(sp)
#     # start time
#     rdcycle s0
#     # touch l1d
#     lw  a0, 0(a0)
#     #end time
#     rdcycle a0
#     # diff end - start
#     sub a0, a0, s0
#     addi	sp,sp,4
#     ret
