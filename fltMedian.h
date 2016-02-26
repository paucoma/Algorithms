
//Minimum Length is 3
#define MEDIAN_LENGTH  7

typedef unsigned int smpl_t;

#define popMedianFilter getFilteredMedian

smpl_t getFilteredMedian(void);
void initMedianFilter(void);
void pushMedianFilter(smpl_t myVal);

/* Main example code
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "fltMedian.h"

int main(){    
  unsigned int i,j,k;
  time_t t;

  srand((unsigned)time(&t));
    
  initMedianFilter();
  printfList();
  //printfListLinks();
  //printf("New Val = %d",k);
  for (i=0; i<32; i++) {
    k=(smpl_t)(rand()%64);
    //printf("New Val = %d",k);
    pushMedianFilter(k);
    //printfList();
    printfOrdList();
    //printfListLinks();
    //printf("\t | Median --> %d\n",getFilteredMedian());
  }
    
  return 0;
}
*/
