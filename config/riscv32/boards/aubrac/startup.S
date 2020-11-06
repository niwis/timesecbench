
.section ".init"


.globl entry
entry:  
  la    sp, __stack_top
  j _start

.globl dome_switch_in_place
dome_switch_in_place:
  csrrw x0, domenextid, a0
  li  t1, 7
  csrrw x0, domenextcap, t1
  csrrw x0, domenextpc, ra

  dome.switch a0
  ret #in case of no dome support