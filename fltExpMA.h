#include <stdio.h>

//Max currently possible is 64 length that is 2^6
#define ExpMA_Nbits  3
//Length of filter is 2^Nbits
//Alpha is effectively 1/Length

typedef unsigned int UINT16_t;

UINT16_t getFltExpMA(void);
void pushFltExpMA(UINT16_t myVal);
void initFltExpMA(void);
