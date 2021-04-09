#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WHITE			0
#define GRAY			1
#define BLACK			2

#define TREE_EDGE		1
#define BACK_EDGE		2
#define FORWARD_EDGE	3
#define CROSS_EDGE	4

#define TRUE			1
#define FALSE			0

typedef struct _vertex{
	int color;
	int f;
	int d;
} Vertex;

typedef struct _VertexInfo{
	int out_degree;
	int * list;
} VertexInfo;

Vertex * vertex;
VertexInfo * vertexInfo;
int numV, time;
int * topoList;
int topo_num=0;
int isDAG = TRUE;

void addEdge(int fromV, int toV){
	int i=0;
	int cur=0;

	for(i=0; i < numV; i++)
	{
		if(vertexInfo[fromV].list[i] == 0)
			break;
		cur ++;
	}
	vertexInfo[fromV].list[cur] = toV;
}

void DFS_Visit(int fromV){
	int i=0, toV;

	/* DISCOVERED */
	time++;
	vertex[fromV].color = GRAY;
	vertex[fromV].d = time;

	for(i=0; i < vertexInfo[fromV].out_degree; i++){
		toV = vertexInfo[fromV].list[i];
		switch(vertex[toV].color)
		{
		case WHITE:
			DFS_Visit(toV);
			break;

		case GRAY:
			isDAG = FALSE;
			break;

		case BLACK:
			break;
		default:
			break;
		}
	}

	/* FINISHED */
	vertex[fromV].color = BLACK;
	topoList[numV-(topo_num++)] = fromV;
	time ++;
	vertex[fromV].f = time;
}

void Sort(int * list, int num)
{
	int i=0, j=0, tmp;

	for(i=0; i < num; i++)
	{
		for(j=i+1; j < num; j++)
		{
			if(list[i] > list[j])
			{
				tmp = list[i];
				list[i] = list[j];
				list[j] = tmp;
			}
		}
	}
}


void DFS(void)
{
	int i;
	for(i=1; i <=numV; i++)
	{
		vertex[i].d = 0;
		vertex[i].f = 0;
		vertex[i].color = WHITE;
		Sort(vertexInfo[i].list, vertexInfo[i].out_degree);
	}

	time = 0;
	for(i=1; i <=numV; i++)
	{
		if(vertex[i].color == WHITE)
		{
			DFS_Visit(i);
		}
	}
}


int main(void)
{
	int i=0, j=0;
	int fromV, toV;

	if(scanf("%d", &numV)>0);

	/* INITIALIZATION START! */
	vertexInfo = (VertexInfo*)malloc(sizeof(VertexInfo)*(numV+1));
	for(i=1; i <=numV; i++){
		vertexInfo[i].list = (int*)malloc(sizeof(int)*numV);
		vertexInfo[i].out_degree = 0;
	}
	for(i=1; i <=numV; i++){
		for(j=0; j < numV; j++){
			vertexInfo[i].list[j] = 0;
		}
	}
	vertex = (Vertex*)malloc(sizeof(Vertex)*(numV+1));
	topoList = (int*)malloc(sizeof(int)*(numV+1));
	/* INITIALIZATION END! */
	

// INPUT
	while(scanf("%d %d", &fromV, &toV)!=EOF){
		addEdge(fromV, toV);
		vertexInfo[fromV].out_degree ++;
	}
	DFS();

// OUTPUT
	printf("%d\n", isDAG);
	if(isDAG)
	{
		for(i=1; i <=numV; i++)
			printf("%d ", topoList[i]);
	}

	return 0;
}


