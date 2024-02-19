/** @file FOSdef.h
 *  Copyright (c) 2023 FigaSystems
 *  FOS Definitions
 *  @author Daniil Dunaef
 *  @date 18-Dec-2023
 *  @bug No current bugs found
*/



#ifndef _FOSDEF_
#define _FOSDEF_

#define IN
#define OUT

#define NULL 0LL

#define FOSAPI __attribute__((stdcall))
#define FOSSYSAPI __attribute__((cdecl))
#define FOSKERNELAPI __attribute__((stdcall))
#define FOSFASTCALL __attribute__((fastcall))
#define FOSINTERRUPT __attribute__((interrupt))

#define FOSKERNEL_VERSION "0.1"

typedef long LONG;
typedef unsigned long ULONG;
typedef LONG *PLONG;
typedef ULONG *PULONG;

typedef char CHAR;
typedef unsigned char UCHAR;
typedef CHAR CCHAR;
typedef CHAR *PCHAR;
typedef UCHAR *PUCHAR;

typedef int INT;
typedef unsigned int UINT;
typedef INT *PINT;
typedef UINT *PUINT;

typedef short SHORT;
typedef unsigned short USHORT;
typedef SHORT *PSHORT;
typedef USHORT *PUSHORT;

typedef void VOID;
typedef VOID *PVOID;

typedef enum {false, true} BOOL;

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

#endif /* !_FOSDEF_! */