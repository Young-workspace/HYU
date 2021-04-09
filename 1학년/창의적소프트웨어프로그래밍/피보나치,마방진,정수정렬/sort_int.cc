#include<iostream>
#include<iomanip>
using namespace std;

void bubbleSort(int num[], int numsort);
int Check(int b);
void put(int b, int *a);
void print(int b, int *a);


int main(void)
{
	int *a;
	int b,count; 
	cin >> b;    
	Check(b);    
	a = new int[b];  

	put(b, a);      

	bubbleSort(a, b);

	print(b,a);     

	delete[] a;      
	a = NULL; 

	return 0;
}


void bubbleSort(int num[], int numsort)
{
	bool exchanges;
	do
	{
		exchanges = false;
		for ( int i = 0; i < numsort - 1; i++ )
		{
			if ( num[i] > num[i + 1] )
			{
				int temp = num[i];
				num[i] = num[i + 1];
				num[i + 1] = temp;
				exchanges = true;    
			}
		}
	}
	while ( exchanges );
}

int Check(int b)
{
	if ( b < 0 || b == 0 )
	{
		exit(0);
	}
}

void put(int b, int *a)
{
	int count;
	for ( count = 0; count < b; count++ )
	{
		cout << "";
		cin >> a[count];     
	}
}

void print(int b, int *a)
{
	int count;
	for ( count = 0; count < b; count++ )
	{
		cout << a[count] << " "<< endl;
	}
}