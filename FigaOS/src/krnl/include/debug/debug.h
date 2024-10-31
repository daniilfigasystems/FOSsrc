#ifndef _DEBUG_
#define _DEBUG_

#include "FOSdef.h"

typedef struct _StackFrame {
  struct StackFrame* ebp;
  unsigned int eip;
} StackFrame;

void 
DBGStackTrace(
    unsigned int MaxFrames
);

#endif