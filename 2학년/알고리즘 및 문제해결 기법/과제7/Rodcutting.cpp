#include<iostream>
#include<stdio.h>

using namespace std;

//first line, integer N given which means the length of Rod (1<=N<=100)
//In the second line, N integers are given which means pi (pi-1 <= pi<=pi+1)
//pi is the value when the length of Rod is 1


int main()
{
	int N, i, j, q;
	cin >>N;
	int *P = new int [N+1];
	
	for(i=1; i<=N; i++)
	{
		cin >> P[i];
	}
	
	int *r  = new int [N+1];
	int *s = new int [N+1];
	
	r[0] = 0;
	for(i = 1; i<=N; i++)
	{
		q = -1;
		for (j = 1; j<=i; j++)
		{
			if(q < (P[j] + r[i-j]))
			{
				q = P[j] + r[i-j];
				s[i] = j;
			}
			r[i] = q;
		}
	}
	
	cout <<r[N]<<'\n';
	while (N>0)
	{
		
		cout << s[N]<<' ';
		N -= s[N];
	}
	cout<<'\n';
	
	delete[] s;
	delete[] r;
	delete[] P;
	return 0;
}
