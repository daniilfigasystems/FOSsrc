global testfpu
testfpu:
mov edx, cr0

and edx, (-1) - (3 + 2);
mov cr0, edx
fninit
fnstsw [.testfpu]
cmp word [.testfpu], 0
jne nofpu
jmp hasfpu
.testfpu: DW 0x55AA
nofpu:
ret 1
hasfpu:
ret 0