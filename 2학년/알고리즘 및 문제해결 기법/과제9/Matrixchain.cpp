#include <iostream>
#include <stdio.h>
using namespace std;

void order ( int i , int j, int *S[]);
int main()
{
	int N, i, j, k;	
	cin >> N;		//number of matrix
	
	
	int P[102], M[101][101];
	for( i = 0; i<N+1; i++)
	{
		cin >> P[i];
	}
	
	int **S = new int *[N];
	
	for(i =1; i<N; i++)
	{
		S[i] = new int [ N+1];
	}
	
	for( i = 1; i<N; i++)
	{
		for(j=2; j<=N; j++)
		{
			S[i][j] = 0;
		}
	}
	int d;
	for(d= 0; d<N; d++)
	{
		for(i = 1; i<=N-d ; i++)
		{
			j = i+d;
			if(j==i)
			{
				M[i][j] = 0;
			}
			else
			{
				M[i][j] = 99999999;
				for(k = i; k<j; k++)
				{
					if (M[i][j] > M[i][k] + M[k+1][j] + P[i-1]*P[k]*P[j])
					{
						M[i][j] = M[i][k] + M[k+1][j] + P[i-1]*P[k]*P[j];
						S[i][j] = k;
					}
					
				}
			}
		}
	}
	
	cout << M[1][N] <<"\n";
	
	order(1, N, S);
	cout << "\n";
	
	return 0;
}

void order ( int i , int j, int *S[])
{
	int k ;
	if(i == j)
	{
		cout <<i << ' ';
	}
	else
	{
		k = S[i][j];
		cout << "(" << ' ';
		order(i, k, S);
		order(k+1, j, S);
		cout << ")"<<' ';
	}
	
}

