#include <iostream>
#include "binary_search.h"

BinarySearch::BinarySearch(){
	mArray = NULL;
	mArrayCount = 0;
}

BinarySearch::BinarySearch(int *array, int _arrayCount){
	int* NewSet = new int[_arrayCount];
	for(int i=0;i<_arrayCount;++i)
		NewSet[i] = array[i];
	mArray = NewSet;
	mArrayCount = _arrayCount;
}

void BinarySearch::sortArray(){
	int tmp;
	for(int i=0;i<mArrayCount;++i){
		for(int j=0;j<mArrayCount-i;++j){	
			if(mArray[j] > mArray[j+1]){
			tmp = mArray[j];
			mArray[j+1] = mArray[j];
			mArray[j+1] = tmp;
			}
		}
	}
}

int BinarySearch::getIndex(int _element){
	int i=0;
	for(int i=0;i<mArrayCount;++i){
		if(mArray[i] == _element)
			return i;
	}
	return -1;
}

BinarySearch::~BinarySearch(){
	delete[] mArray;
}
