#include<iostream>
#include<stdio.h>

using namespace std;

int main()
{
	int N, e1, e2, x1, x2, i, j;

	if ( scanf("%d", &N)>0 );
	if ( scanf("%d%d", &e1, &e2)>0 );
	if ( scanf("%d%d", &x1, &x2)>0 );

	int **S = new int *[3];
	int ** l = new int *[3];
	int **a = new int *[3];
	int **t = new int *[3];
	for ( i = 1; i < 3; i++ )
	{
		S[i] = new int[N+1];
		l[i] = new int[N+1];
		a[i] = new int[N+1];
		t[i] = new int[N+1];
	}

	for ( i = 1; i < 3; i++ )
	{
		for ( j = 1; j < N+1; j++ )
		{
			if(scanf("%d", &a[i][j]) > 0);
		}
	}

	for ( i = 1; i < 3; i++ )
	{
		for ( j = 1; j<N; j++ )
		{
			if(scanf("%d", &t[i][j]) > 0);
		}
	}

	S[1][1] = e1 + a[1][1];
	S[2][1] = e2 + a[2][1];

	for ( i = 2; i < N+1; i++ )
	{
		if ( S[1][i - 1] + a[1][i] <= S[2][i - 1] + t[2][i - 1] + a[1][i] )
		{
			S[1][i] = S[1][i - 1] + a[1][i];
			l[1][i] = 1;
		}
		else
		{
			S[1][i] = S[2][i - 1] + t[2][i - 1] + a[1][i];
			l[1][i] = 2;
		}
		if ( S[2][i - 1] + a[2][i] <= S[1][i - 1] + t[1][i - 1] + a[2][i] )
		{
			S[2][i] = S[2][i - 1] + a[2][i];
			l[2][i] = 2;
		}
		else
		{
			S[2][i] = S[1][i - 1] + t[1][i - 1] + a[2][i];
			l[2][i] = 1;
		}
	}
	
	int min, position; 
	if ( S[1][N] + x1 <= S[2][N] + x2 )
	{
		min = S[1][N] + x1;
		position = 1;
	}
	else
	{
		min = S[2][N] + x2;
		position = 2;
	}
	cout << min << '\n';

	

	i = position;
	int save1[101], save2[101];

	save1[N] = i;
	save2[N] = N;

	for ( j = N; j >= 2; j-- )
	{
		i = l[i][j];
		save1[j - 1] = i;
		save2[j - 1] = j - 1;
	}
	
	for ( i = 1; i < N + 1; i++ )
	{
		cout << save1[i] << ' ' << save2[i] << endl;
	}
	
	
	return 0;
}
