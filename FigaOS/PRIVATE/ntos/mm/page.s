global cr0read
global cr0write
global cr3read
global cr3write
cr0read:
mov eax, cr0
retn
cr0write:
push ebp
mov ebp, esp
mov eax, [ebp+8]
mov cr0,  eax
pop ebp
retn
cr3read:
mov eax, cr3
retn
cr3write:
push ebp
mov ebp, esp
mov eax, [ebp+8]
mov cr3, eax
pop ebp
retn
