typedef struct regs
{
    unsigned int gs, fs, es, ds;      
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;  
    unsigned int int_no, err_code;    
    unsigned int eip, cs, eflags, useresp, ss;   
    unsigned int ax, al, dx, cx;
    unsigned int bl, bh, bx;
    unsigned int di; 
};