/*
 * File: gadgets.s
 * Project: src
 * Created Date: Tuesday July 21st 2020
 * Author: Ronan (ronan.lashermes@inria.fr)
 * -----
 * Last Modified: Monday, 31st August 2020 10:46:08 am
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
    sw a0, 0(a1)
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

.globl get_hart_id
get_hart_id:
    csrrs a0, mhartid, x0 #read current hart id
    ret


.globl wait_for_spy_sync_loop
wait_for_spy_sync_loop:
    fence.i
    j wait_for_spy_sync_loop

.globl wait_for_trojan_sync_loop
wait_for_trojan_sync_loop:
    fence.i
    j wait_for_trojan_sync_loop
    

#write "ret" instruction (0x00008067) at address [a0]
#prevent the compiler to write several sh instruction that can mess up syncXXX functions
.globl pseudo_atomic_ret_write
pseudo_atomic_ret_write:
    lui     t0,0xffff8
    addi	t0,t0,103 # ffff8067 
    li     t1,0xffff
    and     t0, t0, t1
    sw      t0, 0(a0)
    ret
