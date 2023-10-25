#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS

#define PROB 2 // 각각의 문제를 구현하고 해당 문제 번호를 변경하여 테스트

#if PROB == 1
// 1번 문제를 해결하기 위한 프로그램 작성

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000

struct Edge { // 간선을 나타내는 구조체
	int start, end, weight;
};

typedef struct GraphType {
	int en; // 간선의 개수
	int vn; // 정점의 개수
	struct Edge edges[2 * MAX_VERTICES];
} GraphType;

int parent[MAX_VERTICES];

void set_init(int n)
{
	for (int i = 0; i < n; i++)
		parent[i] = -1;
}
// curr가 속하는 집합을 반환한다.
int set_find(int curr)
{
	if (parent[curr] == -1)
		return curr; 			// 루트 
	while (parent[curr] != -1) curr = parent[curr];
	return curr;
}

// 두개의 원소가 속한 집합을 합친다.
void set_union(int a, int b)
{
	int root1 = set_find(a);	// 노드 a의 루트를 찾는다. 
	int root2 = set_find(b);	// 노드 b의 루트를 찾는다. 
	if (root1 != root2) 	// 합한다. 
		parent[root1] = root2;
}

// 그래프 초기화 
void graph_init(GraphType* g)
{
	g->vn = 0;
	g->en = 0;
	for (int i = 0; i < 2 * MAX_VERTICES; i++) {
		g->edges[i].start = 0;
		g->edges[i].end = 0;
		g->edges[i].weight = INF;
	}
}

void set_nodes(GraphType* g, int n)
{
	g->vn = n;
}

// 간선 삽입 연산
void insert_edge(GraphType* g, int start, int end, int w)
{
	g->edges[g->en].start = start;
	g->edges[g->en].end = end;
	g->edges[g->en].weight = w;
	g->en++;
}
// qsort()에 사용되는 함수
int compare(const void* a, const void* b)
{
	struct Edge* x = (struct Edge*)a;
	struct Edge* y = (struct Edge*)b;
	return (x->weight - y->weight);
}

// kruskal의 최소 비용 신장 트리 프로그램
void kruskal(GraphType* g)
{
	int edge_accepted = 0;	                 // 현재까지 선택된 간선의 수	
	int uset, vset;			// 정점 u와 정점 v의 집합 번호
	struct Edge e;
	int total = 0;

	set_init(g->vn);				// 집합 초기화
	qsort(g->edges, g->en, sizeof(struct Edge), compare);

	printf("크루스칼 최소 신장 트리 알고리즘 \n");
	int i = 0;
	while (edge_accepted < (g->vn - 1))	// 간선의 수 < (n-1)
	{
		e = g->edges[i];
		uset = set_find(e.start);		// 정점 u의 집합 번호 
		vset = set_find(e.end);		                 // 정점 v의 집합 번호
		if (uset != vset) {			// 서로 속한 집합이 다르면
			printf("간선 (%d,%d) %d 선택\n\n", e.start, e.end, e.weight);
			edge_accepted++;
			set_union(uset, vset);	// 두개의 집합을 합친다.
			total += e.weight; // 선택된 간선의 가중치를 더한다.
		}
		i++;
	}
	printf("최소 비용 : %d\n", total);
}


int main(void)
{
	GraphType* g;
	g = (GraphType*)malloc(sizeof(GraphType));
	graph_init(g);

	/*
	// test data 1 
	set_nodes(g, 7);
	insert_edge(g, 0, 1, 29);
	insert_edge(g, 1, 2, 16);
	insert_edge(g, 2, 3, 12);
	insert_edge(g, 3, 4, 22);
	insert_edge(g, 4, 5, 27);
	insert_edge(g, 5, 0, 10);
	insert_edge(g, 6, 1, 15);
	insert_edge(g, 6, 3, 18);
	insert_edge(g, 6, 4, 25);
	*/
	// test data 2
	set_nodes(g, 8);
	insert_edge(g, 0, 1, 10);
	insert_edge(g, 0, 3, 6);
	insert_edge(g, 0, 7, 1);
	insert_edge(g, 1, 2, 4);
	insert_edge(g, 1, 5, 2);
	insert_edge(g, 2, 3, 11);
	insert_edge(g, 2, 5, 7);
	insert_edge(g, 3, 7, 3);
	insert_edge(g, 4, 5, 5);
	insert_edge(g, 4, 7, 8);
	insert_edge(g, 5, 6, 9);
	insert_edge(g, 6, 7, 12);
	
	kruskal(g);
	free(g);
	return 0;
}


#elif PROB == 2
// 2번 문제를 해결하기 위한 프로그램 작성
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000L

typedef struct GraphType {
	int n; // 정점의 개수
	int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int selected[MAX_VERTICES];
int distance[MAX_VERTICES];

// 최소 dist[v] 값을 갖는 정점을 반환
int get_min_vertex(int n)
{
	int v, i;
	for (i = 0; i < n; i++)                  // 선택되지 않은 처음 노드 i 선택
		if (!selected[i]) {
			v = i;
			break;
		}
	for (i = 0; i < n; i++) // 선택되지 않은 노드 중 dist가 가장 작은 노드선택하여 v에 할당
		if (!selected[i] && (distance[i] < distance[v])) v = i;
	return (v);
}

void prim(GraphType* g, int s)
{
	int i, u, v;

	for (u = 0; u < g->n; u++)
		distance[u] = INF;

	distance[s] = 0;

	for (i = 0; i < g->n; i++) {
		u = get_min_vertex(g->n);
		selected[u] = TRUE;
		if (distance[u] == INF) return; //연결 안됨

		printf("정점 %d 추가, distance : %d\n", u, distance[u]);
		for (v = 0; v < g->n; v++)
			if (g->weight[u][v] != INF)
				if (!selected[v] && g->weight[u][v] < distance[v])
					distance[v] = g->weight[u][v];

	}
	

	int total_weight = 0;
	for (i = 0; i < g->n; i++)
		total_weight += distance[i];
	printf("최소 비용: %d\n", total_weight);
}

int main(void)
{
	int i;

	/*
	//test data1
	GraphType g = { 7,
	{{ 0, 29, INF, INF, INF, 10, INF },
	{ 29, 0, 16, INF, INF, INF, 15 },
	{ INF, 16, 0, 12, INF, INF, INF },
	{ INF, INF, 12, 0, 22, INF, 18 },
	{ INF, INF, INF, 22, 0, 27, 25 },
	{ 10, INF, INF, INF, 27, 0, INF },
	{ INF, 15, INF, 18, 25, INF, 0 } }
	};
	*/

	//test data2
	GraphType g = { 8,
	{ { 0, 10, INF, 6, INF, INF, INF, 1 },
	{ 10, 0, 4, INF, INF, 2, INF, INF },
	{ INF, 4, 0, 11, INF, 7, INF, INF },
	{ 6, INF, 11, 0, INF, INF, INF, 3 },
	{ INF, INF, INF, INF, 0, 5, INF, 8},
	{ INF, 2, 7, INF, 5, 0, 9, INF },
	{ INF, INF, INF, INF, INF, 9, 0, 12 },
	{ 1, INF, INF, 3, 8, INF, 12, 0 }
	}};
	prim(&g, 0);
	return 0;
}

#endif