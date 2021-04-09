#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;

int Parent(int index) {return index/2;}
int Left(int index){return index*2;}
int Right(int index){return index*2+1;}

void Swap(int arr[], int a, int b)
{
	int tmp;
	tmp = arr[a];
	arr[a] = arr[b];
	arr[b] = tmp;
}

void Max_Heapify(int arr[], int parent, int size)
{
	int left, right, largest;
	left = Left(parent);
	right = Right(parent);
	
	if((right<=size) && (arr[right]>arr[parent]))
	{
		largest=right;
	}
	else
	{ 
		largest = parent;
	}
	
	if((left <=size) && (arr[left]>arr[largest]))
	{
		largest = left;
	}
	if(largest != parent)
	{
		Swap(arr, parent, largest);
		Max_Heapify(arr, largest, size);
	}
}

void Increase_Key(int arr[], int index, int key)
{
	//if(key < arr[index])	{		return ;			}
	arr[index] = key;
	while(index > 1  &&  arr[Parent(index)] < arr[index])
	{
		Swap(arr, index, Parent(index));
		index = Parent(index);
	}
}

int main()
{
	int s, N, index, i;		
	int quit = 0;
	int arr  [100000];
	int ext  [100000];
	int arr_size = 0, ext_size = 0;
	
	while (quit==0)
	{
		if(scanf("%d", &s)>0);
		switch (s)
		{
			case(0):			
				quit = 1;
				break;
				
			case(1):			
				if(scanf("%d", &N)>0);
				arr_size ++;
				arr[arr_size] =N;
				Increase_Key(arr,arr_size, N);
				break;
				
			case(2):			
				ext_size++;
				if(ext_size<1) {return -9999;}
				ext[ext_size] = arr[1];
				Swap(arr, 1, arr_size);
				
				arr_size--;
				Max_Heapify(arr, 1, arr_size);
				
				break;
				
			case(3):	
				if(scanf("%d%d", &index, &N));
				arr[index] = N;
				if(index != 1 && arr[index] > arr[Parent(index)])
				{
					Increase_Key(arr, index, N);
				}
				else
				{
					Max_Heapify(arr,index,arr_size);
				}
				break;
				
			default:
				break;
		}
	}
	
	for (i=1; i<=ext_size; i++)
	{
		printf("%d ", ext[i]);
	}
	printf("\n");
	
	for(i =1; i<=arr_size; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
	
	return 0;
	
}

