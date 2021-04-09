#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;

int  main()
{

	int N, M;
	cin >> N >> M;
	int i = 0;
	int *arr = new int[N];
	for ( ; i < N; i++ )
	{
		cin >> arr[i];
	}

	int  j = 0, k; 
	int index, temp;
	for ( ; j < M; j++ )
	{
		index = j;
		for ( k= j+1; k < N; k++ )
		{
			if ( arr[k] < arr[index] )
			{
				index = k;
			}
		}
		temp = arr[index];
		arr[index] = arr[j];
		arr[j] = temp;
	}
	
	int l = 0;
	for ( ; l < N; l++ )
	{
		cout << arr[l] << '\n';
	}

	return 0;
}
