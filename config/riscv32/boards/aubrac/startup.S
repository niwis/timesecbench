
.section ".init"


.globl entry
entry:  
  la    sp, __stack_top
  j _start
