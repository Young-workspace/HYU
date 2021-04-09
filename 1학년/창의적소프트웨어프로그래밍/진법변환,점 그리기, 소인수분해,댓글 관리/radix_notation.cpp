#include<stdio.h>
#include<iostream>
#include<string>

using namespace std;

// radix 진법, number 쓰고 싶은 숫자
string RadixNotation(unsigned int number, unsigned radix);

int main(int argc, char **argv){
	if ( argc < 2 )						
		return -1;			
	unsigned int radix;					
	sscanf(argv[1], "%u", &radix);
	if ( radix < 2 || radix >36 )		
		return -1;
	for(int i = 2; i < argc; ++i)		
	{
		 unsigned int number;
		sscanf(argv[i], "%u", &number);	
		RadixNotation(number, radix);
	}
	return 0;
}

string RadixNotation(unsigned number, unsigned radix)		//number== convertfrom, radix==convertto
{
	int copy, digit;
	string stringDigit, answer; 
	copy = number;
	while(number!=0){
		digit = number % radix;
		int asciiConversion = 48;
		for(int i = 0; i<16; ++i){			
			if(digit == i){
				stringDigit = asciiConversion;
			}
			asciiConversion +=1;
			if ( asciiConversion == 58 ){
				asciiConversion = 65;
			}
					
		}
		answer = stringDigit +answer;

		number /= radix;
		
	}
	cout << copy << " written in base " << radix << " is:\n" << answer <<endl;
}
