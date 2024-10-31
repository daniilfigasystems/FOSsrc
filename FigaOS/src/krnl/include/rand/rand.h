#define RDSEEDT 0x101
#define RDRANDT 0x010
#define SRANDT 0x111

typedef enum _RNDType
{
    RDSEED = RDSEEDT,
    RDRAND = RDRANDT,
    SRAND = SRANDT
} RNDType;