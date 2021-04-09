#include <stdio.h> 
#include <stdlib.h> 
#include <limits.h> 
#include<iostream>
using namespace std;
 
struct AdjListNode
{
	int dest;
	int weight;
	struct AdjListNode* next;
};
struct AdjList
{
	struct AdjListNode *head;  // pointer to head node of list 
};


struct Graph
{
	int V;
	struct AdjList* array;
};

struct AdjListNode* newAdjListNode(int dest, int weight)
{
	struct AdjListNode* newNode =
		( struct AdjListNode* ) malloc(sizeof(struct AdjListNode));
	newNode->dest = dest;
	newNode->weight = weight;
	newNode->next = NULL;
	return newNode;
}

struct Graph* createGraph(int V)
{
	struct Graph* graph = ( struct Graph* ) malloc(sizeof(struct Graph));
	graph->V = V;

	graph->array = ( struct AdjList* ) malloc(V * sizeof(struct AdjList));

	for ( int i = 0; i < V; ++i )
		graph->array[i].head = NULL;

	return graph;
}

void addEdge(struct Graph* graph, int src, int dest, int weight)
{
	struct AdjListNode* newNode = newAdjListNode(dest, weight);
	newNode->next = graph->array[src].head;
	graph->array[src].head = newNode;

	/*newNode = newAdjListNode(src, weight);
	newNode->next = graph->array[dest].head;
	graph->array[dest].head = newNode;*/
}

// Structure to represent a min heap node 
struct MinHeapNode
{
	int  v;
	int dist;
};

// Structure to represent a min heap 
struct MinHeap
{
	int size;      // Number of heap nodes present currently 
	int capacity;  // Capacity of min heap 
	int *pos;     // This is needed for decreaseKey() 
	struct MinHeapNode **array;
};

// A utility function to create a new Min Heap Node 
struct MinHeapNode* newMinHeapNode(int v, int dist)
{
	struct MinHeapNode* minHeapNode =
		( struct MinHeapNode* ) malloc(sizeof(struct MinHeapNode));
	minHeapNode->v = v;
	minHeapNode->dist = dist;
	return minHeapNode;
}

// A utility function to create a Min Heap 
struct MinHeap* createMinHeap(int capacity)
{
	struct MinHeap* minHeap =
		( struct MinHeap* ) malloc(sizeof(struct MinHeap));
	minHeap->pos = (int *)malloc(capacity * sizeof(int));
	minHeap->size = 0;
	minHeap->capacity = capacity;
	minHeap->array =
		( struct MinHeapNode** ) malloc(capacity * sizeof(struct MinHeapNode*));
	return minHeap;
}

// A utility function to swap two nodes of min heap. Needed for min heapify 
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b)
{
	struct MinHeapNode* t = *a;
	*a = *b;
	*b = t;
}

// A standard function to heapify at given idx 
// This function also updates position of nodes when they are swapped. 
// Position is needed for decreaseKey() 
void minHeapify(struct MinHeap* minHeap, int idx)
{
	int smallest, left, right;
	smallest = idx;
	left = 2 * idx + 1;
	right = 2 * idx + 2;

	if ( left < minHeap->size &&
		minHeap->array[left]->dist < minHeap->array[smallest]->dist )
		smallest = left;

	if ( right < minHeap->size &&
		minHeap->array[right]->dist < minHeap->array[smallest]->dist )
		smallest = right;

	if ( smallest != idx )
	{
		// The nodes to be swapped in min heap 
		MinHeapNode *smallestNode = minHeap->array[smallest];
		MinHeapNode *idxNode = minHeap->array[idx];

		// Swap positions 
		minHeap->pos[smallestNode->v] = idx;
		minHeap->pos[idxNode->v] = smallest;

		// Swap nodes 
		swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);

		minHeapify(minHeap, smallest);
	}
}

// A utility function to check if the given minHeap is ampty or not 
int isEmpty(struct MinHeap* minHeap)
{
	return minHeap->size == 0;
}

struct MinHeapNode* extractMin(struct MinHeap* minHeap)
{
	if ( isEmpty(minHeap) )
		return NULL;

	struct MinHeapNode* root = minHeap->array[0];

	struct MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
	minHeap->array[0] = lastNode;

	minHeap->pos[root->v] = minHeap->size - 1;
	minHeap->pos[lastNode->v] = 0;

	--minHeap->size;
	minHeapify(minHeap, 0);

	return root;
}

void decreaseKey(struct MinHeap* minHeap, int v, int dist)
{

	int i = minHeap->pos[v];

	minHeap->array[i]->dist = dist;


	while ( i && minHeap->array[i]->dist < minHeap->array[( i - 1 ) / 2]->dist )
	{

		minHeap->pos[minHeap->array[i]->v] = ( i - 1 ) / 2;
		minHeap->pos[minHeap->array[( i - 1 ) / 2]->v] = i;
		swapMinHeapNode(&minHeap->array[i], &minHeap->array[( i - 1 ) / 2]);


		i = ( i - 1 ) / 2;
	}
}

bool isInMinHeap(struct MinHeap *minHeap, int v)
{
	if ( minHeap->pos[v] < minHeap->size )
		return true;
	return false;
}

void printArr(int dist[], int n)
{
	int max=0;
	for(int i = 0; i<n; i++)
	{
		if(max<dist[i])
		{
			max = dist[i];
		}
	}
	cout <<max<<endl;
}

void dijkstra(struct Graph* graph, int src)
{
	int V = graph->V;
	int dist[V];

	struct MinHeap* minHeap = createMinHeap(V);


	for ( int v = 0; v < V; ++v )
	{
		dist[v] = INT_MAX;
		minHeap->array[v] = newMinHeapNode(v, dist[v]);
		minHeap->pos[v] = v;
	}

	minHeap->array[src] = newMinHeapNode(src, dist[src]);
	minHeap->pos[src] = src;
	dist[src] = 0;
	decreaseKey(minHeap, src, dist[src]);

	minHeap->size = V;


	while ( !isEmpty(minHeap) )
	{

		struct MinHeapNode* minHeapNode = extractMin(minHeap);
		int u = minHeapNode->v;


		struct AdjListNode* pCrawl = graph->array[u].head;
		while ( pCrawl != NULL )
		{
			int v = pCrawl->dest;

			if ( isInMinHeap(minHeap, v) && dist[u] != INT_MAX &&
				pCrawl->weight + dist[u] < dist[v] )
			{
				dist[v] = dist[u] + pCrawl->weight;


				decreaseKey(minHeap, v, dist[v]);
			}
			pCrawl = pCrawl->next;
		}
	}

	printArr(dist, V);
}


int main()
{
	int V;
	cin >> V;

	struct Graph* graph = createGraph(V);

	int start, edge, end, weight;

	for ( int i = 0; i<V; i++ )
	{
		cin >> start >> edge;
		for ( int j = 0; j<edge; j++ )
		{
			cin >> end >> weight;
			addEdge(graph, start - 1, end - 1, weight);
		}
	}

	dijkstra(graph, 0);

	return 0;
}
