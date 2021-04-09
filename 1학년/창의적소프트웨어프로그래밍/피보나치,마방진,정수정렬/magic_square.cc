#include<iostream>
#include<stdlib.h>
#include<string.h>
using namespace std;

void Magic(int **a,int b);
void Make(int **a, int b);






int main()
{
	int b;
	cin >> b;
	int **a = new int*[b];
	
	Make(a, b);
	Magic(a,b);
	

}

void Magic(int **a, int b)
{
	int num = 1;
	int i = 0;
	int j = ( b / 2 );

	for ( num; num <= b*b; num++ )
	{
		a[i][j] = num;
		if ( ( num ) % b == 0 )      
		{
			i++;

		}
		else if ( i == 0 )			
		{
			i = b - 1;
			j++;
		}
		else if ( j == b - 1 )		
		{
			i--;
			j = 0;
		}
		else						
		{
			i--;
			j++;
		}

	}


	for ( i = 0; i < b ; i++ )
	{
		for ( j = 0; j < b; j++ )
		{
			cout << a[i][j] << " ";
			if ( j == b - 1 )
			{
				cout << endl;
			}
			
		}
	}


	
}

void Make(int **a, int b)
{
	for ( int i = 0; i < b; i++ )      
	{

		a[i] = new int[b];

	}
}