#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;

void Swap(int *arr, int a, int b)
{
	int tmp;
	tmp = arr[a];
	arr[a] = arr[b];
	arr[b] = tmp;
}

void Max_Heapify(int *arr, int parent, int size)
{
	int left, right, largest;
	left = 2*parent+1;
	right = 2*parent +2;
	
	if((left <size) && (arr[left]>arr[parent]))
	{
		largest = left;
	}
	else
	{ 
		largest = parent;
	}
	
	if((right<size) && (arr[right]>arr[largest]))
	{
		largest=right;
	}
	if(largest != parent)
	{
		Swap(arr, parent, largest);
		Max_Heapify(arr, largest, size);
	}
}

void Build_Heap(int *arr, int N)
{
	int parent;
	for(parent = N/2 -1; parent >=0; parent--)
	{
		Max_Heapify(arr, parent, N);
	}
}

void Heap_Sort(int *arr, int N, int k)
{
	Build_Heap(arr, N);
	int last;
	int count = 0;
	
	for(last = N-1; last > 0; last--)
	{
		if(count == k)
		{
			break;
		}
		Swap(arr, 0, last);
		N--;
		count++;
		
		Max_Heapify(arr,0, N);
	}
	
}

int main()
{
	// N: 입력할 개수,  K: biggest element 를 몇 개 출력 할 것인지
	int N, k;
	cin>>N>>k;
	
	int *arr = new int[N];
	int i ;
	for(i = 0; i<N; i++)
	{
		cin>>arr[i];
	}
	
	Heap_Sort(arr, N, k);
	
	for(i = N-1; i>N-1-k; i--)
	{
		cout<<arr[i]<< " ";
	}
	cout<<'\n';
	
	for(i= 0; i<N-k; i++)
	{
		cout <<arr[i]<<" ";
	}
	cout<<'\n';
	
	delete arr;

	
	return 0;
}


