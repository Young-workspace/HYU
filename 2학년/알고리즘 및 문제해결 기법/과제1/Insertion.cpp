
#include<stdio.h>
#include<iostream>
using namespace std;



void Insertion(int arr[], int size)
{
	int i, j;
	for( i = 1; i<size; i++)
	{
		 j = i;
		while(j>0 && arr[j-1] < arr[j]){
			swap(arr[j-1], arr[j]);
			j--;
		}
	}
}

int main()
{
	int N,  i, j;
	
	cin >> N;
	
	int *arr = new int[N];
	
	for(i = 0; i<N; i++)
	{
		cin>>arr[i];
	}
	
	Insertion(arr,N);
	
	for(j = 0; j<N; j++)
	{
		cout<<arr[j]<<"\n";
	}
	
	
	delete []arr;
	
	return 0;
	
}

