
.section ".init"


.globl entry
entry:  
  la    sp, __stack_top
  j _start





  

.globl dome_switch_in_place
dome_switch_in_place:
  ret #in case of no dome support