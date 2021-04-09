#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

#define MAX_TREE_HT 800
struct MinHeapNode
{
	char data;  // One of the input characters
	int freq;  // Frequency of the character
	struct MinHeapNode *left, *right; // Left and right child of this node
};

struct MinHeap
{
	int size;    // Current size of min heap
	int capacity;   // capacity of min heap
	struct MinHeapNode **array;  // Attay of minheap node pointers
};

struct MinHeapNode* newNode(int freq)
{
	struct MinHeapNode* temp =
		( struct MinHeapNode* ) malloc(sizeof(struct MinHeapNode));
	temp->left = temp->right = NULL;
	temp->freq = freq;
	return temp;
}

struct MinHeap* createMinHeap(int capacity)
{
	struct MinHeap* minHeap =
		( struct MinHeap* ) malloc(sizeof(struct MinHeap));
	minHeap->size = 0;  // current size is 0
	minHeap->capacity = capacity;
	minHeap->array =
		( struct MinHeapNode** )malloc(minHeap->capacity * sizeof(struct MinHeapNode*));
	return minHeap;
}

void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b)
{
	struct MinHeapNode* t = *a;
	*a = *b;
	*b = t;
}

void minHeapify(struct MinHeap* minHeap, int idx)
{
	int smallest = idx;
	int left = 2 * idx + 1;
	int right = 2 * idx + 2;

	if ( left < minHeap->size &&
		minHeap->array[left]->freq < minHeap->array[smallest]->freq )
		smallest = left;

	if ( right < minHeap->size &&
		minHeap->array[right]->freq < minHeap->array[smallest]->freq )
		smallest = right;

	if ( smallest != idx )
	{
		swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
		minHeapify(minHeap, smallest);
	}
}

int isSizeOne(struct MinHeap* minHeap)
{
	return ( minHeap->size == 1 );
}

struct MinHeapNode* extractMin(struct MinHeap* minHeap)
{
	struct MinHeapNode* temp = minHeap->array[0];
	minHeap->array[0] = minHeap->array[minHeap->size - 1];
	--minHeap->size;
	minHeapify(minHeap, 0);
	return temp;
}

void insertMinHeap(struct MinHeap* minHeap, struct MinHeapNode* minHeapNode)
{
	++minHeap->size;
	int i = minHeap->size - 1;
	while ( i && minHeapNode->freq < minHeap->array[( i - 1 ) / 2]->freq )
	{
		minHeap->array[i] = minHeap->array[( i - 1 ) / 2];
		i = ( i - 1 ) / 2;
	}
	minHeap->array[i] = minHeapNode;
}

void buildMinHeap(struct MinHeap* minHeap)
{
	int n = minHeap->size - 1;
	int i;
	for ( i = ( n - 1 ) / 2; i >= 0; --i )
		minHeapify(minHeap, i);
}

int isLeaf(struct MinHeapNode* root)
{
	return !( root->left ) && !( root->right );
}

struct MinHeap* createAndBuildMinHeap(int freq[], int size)
{
	struct MinHeap* minHeap = createMinHeap(size);
	for ( int i = 0; i < size; ++i )
		minHeap->array[i] = newNode(freq[i]);
	minHeap->size = size;
	buildMinHeap(minHeap);
	return minHeap;
}

struct MinHeapNode* buildHuffmanTree(int freq[], int size)
{
	struct MinHeapNode *left, *right, *top;

	struct MinHeap* minHeap = createAndBuildMinHeap(freq, size);

	while ( !isSizeOne(minHeap) )
	{
		left = extractMin(minHeap);
		right = extractMin(minHeap);

		top = newNode(left->freq + right->freq);
		top->left = left;
		top->right = right;
		insertMinHeap(minHeap, top);
	}

	return extractMin(minHeap);
}

int sum = 0;
int check = 0;
void printCodes(struct MinHeapNode* root, int arr[], int top)
{
	if ( root->left )
	{
		arr[top] = 0;
		printCodes(root->left, arr, top + 1);
	}
	if ( root->right )
	{
		arr[top] = 1;
		printCodes(root->right, arr, top + 1);
	}
	if ( isLeaf(root) )
	{
		check = top - 1;
		/*
		cout << root->freq << ' ';
		cout << check << endl;
		*/
		sum += check * root->freq;
	}
	
	
}


void HuffmanCodes(int freq[], int size)
{
	struct MinHeapNode* root = buildHuffmanTree(freq, size);
	int arr[MAX_TREE_HT], top = 1;
	printCodes(root, arr, top);
	
	cout << sum << endl;


}

int main()
{
	int N, i, j, S;
	cin >> N;

	char **C = new char *[N + 1];	//character
	int *freq = new int[N + 1];	//frequency
	for ( i = 0; i< N ; i++ )
	{
		C[i] = new char[6];
		for ( j = 0; j<4; j++ )
		{
			cin >> C[i][j];
		}
		cin >> freq[i];
	}

	cin >> S;

	int k = 0;
	int m = N;
	while( m >2)
	{
		m = m/2;
		k++;
	}
	if(m>0)
	{
		k++;
	}

	
			
	
	cout << S * k << '\n';
	HuffmanCodes(freq, N);

	return 0;
}
