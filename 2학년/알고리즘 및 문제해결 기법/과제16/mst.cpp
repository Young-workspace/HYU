#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>
using namespace std;

#define edge pair<int,int>

class Graph
{
private:
	vector<pair<int, edge> > G; // graph
	vector<pair<int, edge> > T; // mst
	int *parent;
	int V; // number of vertices/nodes in graph
public:
	Graph(int V);
	void AddWeightedEdge(int u, int v, int w);
	int find_set(int i);
	void union_set(int u, int v);
	void kruskal();
	void print();
};


Graph::Graph(int V)
{
	parent = new int[V];

	for ( int i = 0; i < V; i++ )
		parent[i] = i;

	G.clear();
	T.clear();
}
void Graph::AddWeightedEdge(int u, int v, int w)
{
	G.push_back(make_pair(w, edge(u, v)));
	G.push_back(make_pair(w, edge(v,u)));
}
int Graph::find_set(int i)
{
	if ( i == parent[i] )
		return i;
	else
		return find_set(parent[i]);
}

void Graph::union_set(int u, int v)
{
	parent[u] = parent[v];
}
void Graph::kruskal()
{
	int i, uRep, vRep;
	sort(G.begin(), G.end()); 
	for ( i = 0; i < (int)G.size(); i++ )
	{
		uRep = find_set(G[i].second.first);
		vRep = find_set(G[i].second.second);
		if ( uRep != vRep )
		{
			T.push_back(G[i]); 
			if(uRep<=vRep)
			{
				union_set(uRep,vRep);
			}
			else
			{
				union_set(vRep, uRep);
			}
		}
	}
	print();
}
void Graph::print()
{
	int a = (int)T.size();
	printf("%d\n", a);
	for ( int i = 0; i < (int)T.size(); i++ )
	{
		printf("%d %d %d\n", T[i].second.first + 1, T[i].second.second + 1, T[i].first);
	}
}
int main()
{
	int N;
	//cin >> N;
	if(scanf("%d", &N) >0);
	Graph g(N);
	int x, y, w;
	while ( scanf("%d %d %d", &x, &y, &w) != EOF )
	{
		g.AddWeightedEdge(x - 1, y - 1, w);
	}
	
	g.kruskal();
	return 0;
}


