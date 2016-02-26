/* Exponential Moving Average window
    ExpMA_LENGTH    - Constant defining the length
    
    y_0 = y_{-1} + (x_0 - y_{-1})/N
    
    Fractional bits need to be Log_2(2*N)
        2->2, 4->3, 8->4, 16->5, 32->6, 64->7, 
        128->8, 
        256->9, 512->10, 1024->11, 2048->12, 4096->13, 8192->14, 16384->15
    Local variables require 1 more bit to be able to handle negative values
    
    We are going to set this us for 16 bit sample input.
    
    signed short long   24 bits
    unsigned short long 24 bits
    
    with 24 bits we can do up to 64 sample window on 16 bit value
    with 32 bits we can do up to 16384 sample window on 16 bit value
    For now we will limit to 24 bits
*/

#include "fltExpMA.h"

//typedef unsigned short long emaSS_t;
typedef unsigned long emaSS_t;
//exponential moving average Storage Sample type

//typedef signed short long SINT24_t;
typedef signed long SINT24_t;

static emaSS_t mEMA;

void initFltExpMA(void){
    mEMA = 0;
}

//y_0 = y_{-1} + (x_0 - y_{-1})/N
void pushFltExpMA(UINT16_t myVal){
    SINT24_t myTemp;
    //y_{-1} = mEMA
    myTemp = myVal<<(ExpMA_Nbits+1);
    myTemp -= mEMA;
    myTemp >>= ExpMA_Nbits;
    mEMA += myTemp;
}

UINT16_t getFltExpMA(void){
    emaSS_t myRet;
    myRet = mEMA>>(ExpMA_Nbits);
    //Now we handle the round up/down case
    myRet++;
    myRet >>= 1;
    return((UINT16_t)myRet);
}
