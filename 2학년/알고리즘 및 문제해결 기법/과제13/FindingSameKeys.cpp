#include <stdio.h>
#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
	int N, M;
	cin >> N>>M;
	
	int *A = new int [N];
	int *B = new int[M];
	
	int i;
	for( i = 0; i<N; i++)
	{
		cin>>A[i];
	}
	
	for( i = 0; i<M; i++)
	{
		cin >> B[i];
	}
	
	int count = 0;
	sort(A, A+N);
	sort(B, B+M);
	int j = 0;
	for( i = 0; i<N; )
	{
		if(A[i] == B[j])
		{
			count ++;
			i++;
		}
		else if(A[i] < B[j])
		{
			i++;
		}
		else if(A[i] > B[j])
		{
			j++;
		}
	}
	cout <<count << endl;
}
