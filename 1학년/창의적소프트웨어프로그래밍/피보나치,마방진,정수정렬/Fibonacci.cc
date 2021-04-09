#include<iostream>
using namespace std;

int Fibonacci(int n);
void Check(int n);
void Call(int n);


int main()
{
	int n;
	cin >> n;
	Check(n);
	Call(n);
}

int Fibonacci(int n)
{
	
		if ( i == 0 )
		{
			return 0;
		}
		else if ( i == 1 )
		{
			return 1;
		}
		else
		{
			return Fibonacci(i-1) + Fibonacci(i-2);

		}

	return 0;
	
	
}

void Check(int n)
{
	if ( n < 0 || n>45 )
	{
		cout << "error";
	}
}

void Call(int n)
{
	for(int i=0; i<n; i++){
		Fibonacci(n);
	}
	
}