#include "stdio.h"
#include "fltMedian.h"

// supported are median lengths of odd numbers from 3..15
// 	 if longer lengths are required the indexes should be adjusted.
// 	 - We use 4 bits to index each value 
#define MAX_ITEMS MEDIAN_LENGTH
#define LL_NULL	MAX_ITEMS
#define MEDIAN_IDX	MEDIAN_LENGTH/2

typedef unsigned char idx_t;

typedef struct{
  smpl_t value;    // sample value (24 bits)
  idx_t next;
  idx_t prev;
}node_t;

static node_t	mLList[MAX_ITEMS];
static idx_t    mIdxLow;
static idx_t    mIdxOld;

/* ------ Local Function prototypes ------ */
idx_t getMedianPos(void);

void printfOrdList(void){
  idx_t i;
  i = mIdxLow;
  printf("\n|");
  while(i != LL_NULL){
    printf(" %d\t|",mLList[i].value);
    i = mLList[i].next;
  }
}
void printfList(void){
  idx_t i;
  printf("\n------------------------------\n");   
  for(i=0;i<MAX_ITEMS;i++)
    printf("| %d\t",mLList[i].value);
}
void printfListLinks(void){
  idx_t i;
  printf("------------------------------\n");    
  for(i=0;i<MAX_ITEMS;i++)
    printf("\t %d <-- [%d] --> %d \n",mLList[i].prev,i,mLList[i].next);
  printf("\n------------------------------\n");
}

//Returns the current median
smpl_t getFilteredMedian(void){
	idx_t myIdx;
	myIdx = getMedianPos();
	return mLList[myIdx].value;
}

void initMedianFilter(void){
	idx_t i;
	for(i=0;i<MAX_ITEMS;i++){
		mLList[i].value = 0;
		mLList[i].next = i+1;
		mLList[i].prev = i-1;
	}	
	mLList[MAX_ITEMS-1].next = LL_NULL;
	mLList[0].prev = LL_NULL;
	mIdxLow = 0;
	mIdxOld = 0;
}
// we will not make any control on if it is full or not,
//   the median array is assumed always full.
//   - we first remove the oldest, add the newest and then sort it.
void pushMedianFilter(smpl_t myVal){
  idx_t i,myPrev,myNext;

	myPrev = mLList[mIdxOld].prev;
	myNext = mLList[mIdxOld].next;
	//Check if we are loosing our lowest value
	if(mIdxOld == mIdxLow) mIdxLow = myNext;
	// We remove the current object from the linked list
	if (myPrev != LL_NULL) mLList[myPrev].next = myNext;
	if (myNext != LL_NULL) mLList[myNext].prev = myPrev;
	// We replace the last value with the new
	mLList[mIdxOld].value = myVal;
	
	myNext = getMedianPos();
    myPrev = LL_NULL;
    i = 0;
    while ((myNext != LL_NULL) && (i != LL_NULL)){
		myPrev = myNext;
		if(myVal > mLList[myNext].value){
			myNext = mLList[myNext].next;
            if(i == 1) {
                i=LL_NULL; //Change direction detected
                //myIdx.prev = mLList[myIdx.next].next;
            }else{
                //myIdx.next = mLList[myIdx.next].next;
                i=2;
            }
		}else{
			if(i == 2){
			    i=LL_NULL; //Change direction detected
			    myPrev = mLList[myNext].prev;
			}else{
			    myNext = mLList[myNext].prev;
			    i=1;
			} 
		}
	}
	
	//Now myIdx.prev holds the item who we should insert just after
	//  - so prev = prev, next = prev.next
	//  Unless next is null:
	//    if next is null we don't know if we are at the end of the begining
	//      - prev holds the last comparison point

	if (myNext == LL_NULL){
		//if(myVal > mLList[myIdx.prev].value){
		if(i==2){
			//We need to add at the end of the list	
			mLList[mIdxOld].prev = myPrev;
			mLList[mIdxOld].next = myNext;  //Null in this case
			mLList[myPrev].next = mIdxOld;	//Adding at the end
		}else{
			//we need to add at the start of the list
		  mLList[mIdxOld].prev = myNext;	//Null in this case
		  mLList[mIdxOld].next = myPrev;
		  mLList[myPrev].prev = mIdxOld;	//Adding infront
		  //!! We have a new Low
		  mIdxLow = mIdxOld;
		}
	}else{
		mLList[mIdxOld].prev = myPrev;
		//myIdx.next = mLList[myIdx.prev].next;
		mLList[mIdxOld].next = myNext;
		//Slot the new value in the middle
		mLList[myPrev].next = mIdxOld;
		mLList[myNext].prev = mIdxOld;
	}

	// We move to the next last item
	mIdxOld++;
	if (mIdxOld == MAX_ITEMS) mIdxOld = 0;
}

//inline
idx_t getMedianPos(void){
	idx_t i,myRet;
	myRet = mIdxLow;
	while ((i < MEDIAN_IDX) && (myRet != LL_NULL)){
		myRet = mLList[myRet].next;
		i++;
	}
	return myRet;
}
