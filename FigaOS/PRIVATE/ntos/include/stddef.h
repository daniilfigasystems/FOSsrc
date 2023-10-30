#define NULL 0
#define low_16(address) (unsigned short)((address) & 0xFFFF)
#define high_16(address) (unsigned short)(((address) >> 16) & 0xFFFF)
#define low_32(address) (unsigned int)((address) & 0xFFFF)
#define high_32(address) (unsigned int)(((address) >> 24) & 0xFFFF)
typedef unsigned int size_t;
