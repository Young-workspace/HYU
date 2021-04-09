#include <iostream>
#include "simple_int_set.h"

using namespace std;

SimpleIntSet::SimpleIntSet(int *_elements, int _count){
	if(_count <= MAX_SIZE){
 	mElementCount = _count;
 	int* NewSet = new int[_count];
 	for(int i=0;i<mElementCount;++i)
		NewSet[i] = _elements[i];
	mElements = NewSet;
	}
}

void SimpleIntSet::sortElements(){
	int tmp;
	for (int i = 0; i < mElementCount; ++i) {
		for (int j = 0; j < mElementCount-i-1; ++j) {	
			if (mElements[j] > mElements[j + 1]) {
				tmp = mElements[j + 1];
				mElements[j + 1] = mElements[j];	
				mElements[j] = tmp;
			}
		}
	}
	for (int j = 0; j < mElementCount; ++j)	{
			if(mElements[j] == mElements[j + 1]){
			for(int i=j;i<mElementCount;++i)
			mElements[i] = mElements[i + 1];
			(this ->mElementCount)--;
		}	
	}
}

int * SimpleIntSet::elements() const{ return this -> mElements; }
int SimpleIntSet::elementCount() const{  return this -> mElementCount; }

SimpleIntSet* SimpleIntSet::unionSet(SimpleIntSet& _operand){
	this -> sortElements();
	(& _operand)-> sortElements();
	int i;
	int count = this->mElementCount + (& _operand)->mElementCount;
	int* NewSet = new int[count];
	for(i=0;i<this->mElementCount;++i){
		NewSet[i] = this->mElements[i];
	}
	int k = (&_operand) -> mElementCount;
	for(int j=0;j<k;++i,++j){
		NewSet[i] = (& _operand)->mElements[j];	
	}
	this -> mElementCount = count;
	this->mElements = NULL;
	this -> mElements = NewSet;
	SimpleIntSet::sortElements();
}

SimpleIntSet* SimpleIntSet::differenceSet(SimpleIntSet& _operand){
	this -> sortElements();
	(& _operand)-> sortElements();
	for(int i=0;i<this->mElementCount;++i){
		for(int j=0;j<(& _operand)->mElementCount;++j){
		if(this->mElements[i] == (& _operand)->mElements[j]){
		for(;i<(this->mElementCount);++i)
			this ->mElements[i]= this ->mElements[i+1];
		(this->mElementCount)-=1;
		i=0;
			}
		}
	}
}

SimpleIntSet* SimpleIntSet::intersectSet(SimpleIntSet& _operand){
	this -> sortElements();
	(& _operand)-> sortElements();
	int count = this -> mElementCount;
	int k=0;
	int* NewSet = new int[count];
	for(int i=0;i<this->mElementCount;++i){
	for(int j=0;j<(&_operand)->mElementCount;++j){
		if(this->mElements[i] == (&_operand) ->mElements[j]){
			NewSet[k] =  this->mElements[i];
			++k;
		}
	}
}
	this -> mElementCount = k;
	this->mElements = NULL;
	this -> mElements = NewSet;
	SimpleIntSet::sortElements();
}

void SimpleIntSet::printSet(){
	cout << "{ ";
	for(int i=0; i<SimpleIntSet::elementCount();++i)
		cout << mElements[i] <<" ";
	cout << "}"<<endl;
}


SimpleIntSet::~SimpleIntSet(){
	delete[] mElements;
}
