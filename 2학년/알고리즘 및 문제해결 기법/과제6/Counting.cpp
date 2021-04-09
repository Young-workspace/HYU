#include<stdio.h>
#include<iostream>
using namespace std;


int main()
{
	int N, M, K;
	//cin >> N >> M >> K;
	if(scanf("%d%d%d", &N, &M, &K)>0);
	
	int *A = new int [K];
	int *B = new int[K];
	int *C = new int [M];
	
	int i, key;
	for ( i = 1; i<K+1; i++ )
	{
		if(scanf("%d%d", &A[i], &B[i])>0);
		//cin >> A[i] >> B[i];
	}

	for ( i = 1; i<M+1; i++ )
	{
		C[i] = 0;
	}
	
	for ( i = 1; i<N+1; i++ )
	{
		//cin >> key;
		if(scanf("%d", &key)>0);
		C[key]++;
	}

	for(i =2; i<M+1; i++)
	{
		C[i] += C[i-1];
	}
	
	for(i = 1; i<K+1; i++)
	{
		cout<<C[B[i]] - C[A[i]-1]<<"\n";
	}




	return 0;
}
