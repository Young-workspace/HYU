#include<iostream>
#include<stdio.h>
#include<math.h>

using namespace std;

string primeFactorization(unsigned int number);

int main(int argc, char **argv){
		if(argc<1){
			return -1;
		}
		unsigned int number;
		sscanf(argv[1],"%u",&number);

		primeFactorization(number);
		return 0;
}

string primeFactorization(unsigned int number){
	int save;
	int loop_2 = 0;
	int loop_3 = 0;

		
		

	 if(number%2==0 &&number%3==0){		// 2랑 3으로 나눠지면
		while(number!=1){				// 1이 될 때까지
			if(number%2 ==0){			//2로 나눔
				number/=2;
				loop_2++;
			}
			else if(number%3 == 0){		//3으로 나눔
				number/=3;
				loop_3++;
			}
			else{						//안 나눠질떄
				save = number;
				number =1;
			}
				
		}	
		cout<<2<<"^"<<loop_2<<"x"<<3<<"^"<<loop_3;
		if (save>3){
			cout<<"x"<<save<<"^"<<1;
		}
		cout<<endl;
	}
	else{
		cout<<number<<"^"<<1<<endl;
	}
		
		
		
		

	
	




}