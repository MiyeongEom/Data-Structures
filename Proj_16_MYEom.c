#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define _CRT_SECURE_NO_WARNINGS
#define PROB 3 // 각각의 문제를 구현하고 해당 문제 번호를 변경하여 테스트

#if PROB == 1
#define TRUE 1
#define FALSE 0
#define PROB 1

#define MAX_VERTICES 100
#define INF 10000 /* 무한대 (연결이 없는 경우) */

typedef struct GraphType {
	int n; // 정점의 개수
	int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int distance[MAX_VERTICES];/* 시작정점으로부터의 최단경로 거리 */
int found[MAX_VERTICES]; /* 방문한 정점 표시 */
int path[MAX_VERTICES];/* 경유 노드 */

int choose(int distance[], int n, int found[])
{
	int i, min, minpos;
	min = INT_MAX;
	minpos = -1;
	for (i = 0; i < n; i++)
		if (distance[i] < min && !found[i]) {
			min = distance[i];
			minpos = i;
		}
	return minpos;
}

void print_status(GraphType* g)
{
	printf("Distance: ");
	for (int i = 0; i < g->n; i++) {
		if (distance[i] == INF)
			printf("INF ");
		else
			printf("%d ", distance[i]);
	}
	printf("\n");

	printf("Found: ");
	for (int i = 0; i < g->n; i++) {
		printf("%d ", found[i]);
	}
	printf("\n\n");

	Sleep(1000);  // 1초 대기 (Windows 전용)
}

void shortest_path(GraphType* g, int start)
{
	int i, u, w;
	for (i = 0; i < g->n; i++) /* 초기화 */
	{
		distance[i] = g->weight[start][i];
		found[i] = FALSE;
	}
	found[start] = TRUE;    /* 시작 정점 방문 표시 */
	distance[start] = 0;
	for (i = 0; i < g->n - 1; i++) {
		print_status(g);
		u = choose(distance, g->n, found);
		found[u] = TRUE;
		for (w = 0; w < g->n; w++)
			if (!found[w]) {
				if (distance[u] + g->weight[u][w] < distance[w]) {
					distance[w] = distance[u] + g->weight[u][w];
					path[w] = u;
				}
			}
	}
}


void print(GraphType* g, int start, int end)
{
	printf("index : ");
	for (int i = 0; i < g->n; i++) {
		printf("%d ", i);
	}
	printf("\n");

	printf("path[i]: ");
	for (int i = 0; i < g->n; i++) {
		printf("%d ", path[i]);
	}
	printf("\n");
}

void print_path(GraphType* g, int start, int end)
{

	if (distance[end] == INF) {
		printf("경로 없음");
		return;
	}

	int path_stack[MAX_VERTICES];
	int index_stack[MAX_VERTICES];
	int stack_top = 0;

	int current_vertex = end;
	while (current_vertex != start) {
		path_stack[stack_top++] = current_vertex;
		current_vertex = path[current_vertex];
	}

	printf("정점 %d에서 정점 %d까지의 경로: ", start, end);
	printf("%d ", start);
	for (int i = stack_top - 1; i >= 0; i--) {
		printf("-> %d ", path_stack[i]);
	}
	printf("\n");
}

int main(void)
{
	int end;

	// test data 1
	/*
	GraphType g = { 7,
	{{ 0, 7, INF, INF, 3, 10, INF },
	{ 7, 0, 4, 10, 2, 6, INF },
	{ INF, 4, 0, 2, INF, INF, INF },
	{ INF, 10, 2, 0, 11, 9, 4 },
	{ 3, 2, INF, 11, 0, INF, 5 },
	{ 10, 6, INF, 9, INF, 0, INF },
	{ INF, INF, INF, 4, 5, INF, 0 } }
	};
	*/

	// 방향성 그래프에도 적용 가능
	// test data 2
	
	GraphType g = {6,
	{{ 0, 50, 45, 10, INF, INF},
	{ INF, 0, 10, 15, INF, INF},
	{ INF, INF, 0, INF, 30, INF},
	{ 20, INF, INF, 0, 15, INF},
	{ INF, 20, 35, INF, 0, INF},
	{ INF, INF, INF, INF, 3, 0}}
	};
	

	/*
	// test data 3
	GraphType g = { 7,
	{{ 0, 7, INF, 5,INF, INF, INF},
	{ 7, 0, 8, 9, 7, INF, INF},
	{ INF, 8, 0, INF, 5, INF, INF},
	{ 5, 9, INF, 0, 15, 6, INF },
	{ INF, 7, 5, 15, 0, 8, 9},
	{ INF, INF, INF, 6, 8, 0, 11 },
	{ INF, INF, INF, INF, 9, 11, 0 } }
	};
	*/

	shortest_path(&g, 0);
	end = 5;
	print(&g, 0, end);
	printf("\n정점 %d에서 정점 %d까지의 경로 : ", 0, end);
	print_path(&g, 0, end); // 정점 0에서 정점 end으로 가는 최단경로 출력
	printf("\n");
	return 0;
}


#elif PROB == 2
#define MAX_VERTICES 100
#define INF 1000000 /* 무한대 (연결이 없는 경우) */
typedef struct GraphType {
	int n; // 정점의 개수
	int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;
int A[MAX_VERTICES][MAX_VERTICES];
int path[MAX_VERTICES][MAX_VERTICES];

void printA(GraphType* g) {
	int i, j, n;
	printf("      ");
	for (n = 0; n < g->n; n++)
		printf("%3d", n);
	printf("\n");
	printf("===============================\n");
	for (i = 0; i < g->n; i++) {
		printf("%3d  ||", i);
		for (j = 0; j < g->n; j++) {
			if (A[i][j] == INF)
				printf(" * ");
			else printf("%3d", A[i][j]);
		}
		printf("\n");
	}
	printf("===============================\n");
	printf("\n");
}

void floyd(GraphType* g)
{

	int i, j, k;
	for (i = 0; i < g->n; i++) {
		for (j = 0; j < g->n; j++) {
			A[i][j] = g->weight[i][j];
			if (i != j && A[i][j] != INF)
				path[i][j] = i;
			else
				path[i][j] = -1;
		}
	}
		printA(g);


	for (k = 0; k < g->n; k++) {
		printf("k = %d\n", k);
		for (i = 0; i < g->n; i++)
			for (j = 0; j < g->n; j++)
				if (A[i][k] + A[k][j] < A[i][j]) {
					A[i][j] = A[i][k] + A[k][j];
					path[i][j] = path[k][j];
				}
		printA(g);
	}
}

void print_path(int path[][MAX_VERTICES], int start, int end)
{
	if (path[start][end] == INF) {
		printf("경로 없음\n");
		return;
	}

	int path_stack[MAX_VERTICES];
	int stack_top = 0;

	int current_vertex = end;
	while (current_vertex != start) {
		path_stack[stack_top] = current_vertex;
		current_vertex = path[start][current_vertex];
		stack_top++;
	}

	printf("%d ", start);
	for (int i = stack_top - 1; i >= 0; i--) {
		printf("-> %d ", path_stack[i]);
	}
	printf("\n");
}

int main(void)
{
	int start, end;
	
	// test data 1
	GraphType g = { 7,
	{{ 0, 7, INF, INF, 3, 10, INF },
	{ 7, 0, 4, 10, 2, 6, INF },
	{ INF, 4, 0, 2, INF, INF, INF },
	{ INF, 10, 2, 0, 11, 9, 4 },
	{ 3, 2, INF, 11, 0, INF, 5 },
	{ 10, 6, INF, 9, INF, 0, INF },
	{ INF, INF, INF, 4, 5, INF, 0 } }
	};
	/*
	// test data 2
	GraphType g = { 7,
	{{ 0, 7, INF, 5,INF, INF, INF},
	{ 7, 0, 8, 9, 7, INF, INF},
	{ INF, 8, 0, INF, 5, INF, INF},
	{ 5, 9, INF, 0, 15, 6, INF },
	{ INF, 7, 5, 15, 0, 8, 9},
	{ INF, INF, INF, 6, 8, 0, 11 },
	{ INF, INF, INF, INF, 9, 11, 0 } }
	};
	*/
	floyd(&g);
	start = 0; end = 3;
	printf("\n정점 %d에서 정점 %d까지의 경로 : ", start, end);
	print_path(path, start, end); // 정점 start에서 정점 end으로 가는 최단경로 출력
	printf("\n");
	return 0;
}

#elif PROB == 3
#define MAX_VERTICES 50

typedef struct GraphNode
{
	int vertex;
	struct GraphNode* link;
} GraphNode;

typedef struct GraphType {
	int n; // 정점의 개수
	GraphNode* adj_list[MAX_VERTICES];
} GraphType;

void graph_init(GraphType* g) {
	int v;
	g->n = 0;
	for (v = 0; v < MAX_VERTICES; v++)
		g->adj_list[v] = NULL;
}

void insert_vertex(GraphType* g, int v) {
	if (((g->n) + 1) > MAX_VERTICES) {
		fprintf(stderr, "그래프: 정점의 개수 초과");
		return;
	}
	g->n++;
}

void insert_edge(GraphType* g, int u, int v) {
	GraphNode* node;
	if (u >= g->n || v >= g->n) {
		fprintf(stderr, "그래프 : 정점 번호 오류");
		return;
	}
	node = (GraphNode*)malloc(sizeof(GraphNode));
	node->vertex = v;
	node->link = g->adj_list[u];
	g->adj_list[u] = node;
}

#define MAX_STACK_SIZE 100
typedef int element;
typedef struct {
	element stack[MAX_STACK_SIZE];
	int top;
}StackType;

void init(StackType* s) {
	s->top = -1;
}

int is_empty(StackType* s) {
	return(s->top == -1);
}

int is_full(StackType* s) {
	return (s->top == (MAX_STACK_SIZE - 1));
}

void push(StackType* s, element item) {
	if (is_full(s)) {
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else s->stack[++(s->top)] = item;
}

element pop(StackType* s) {
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->stack[(s->top)--];
}

int topo_sort(GraphType* g)
{
	int i;
	StackType s;
	GraphNode* node;

	// 모든 정점의 진입 차수를 계산
	int* in_degree = (int*)malloc(g->n * sizeof(int));
	for (i = 0; i < g->n; i++)			// 초기화
		in_degree[i] = 0;
	for (i = 0; i < g->n; i++) {
		GraphNode* node = g->adj_list[i];//정점 i에서 나오는 간선들
		while (node != NULL) {
			in_degree[node->vertex]++;
			node = node->link;
		}
	}

	// 진입 차수가 0인 정점을 스택에 삽입
	init(&s);
	for (i = 0; i < g->n; i++) {
		if (in_degree[i] == 0) push(&s, i);
	}
	// 위상 순서를 생성 
	while (!is_empty(&s)) {
		int w;
		w = pop(&s);
		printf("정점 %d ->", w);		//정점 출력
		node = g->adj_list[w];	//각 정점의 진입 차수를 변경
		while (node != NULL) {
			int u = node->vertex;
			in_degree[u]--;			//진입 차수를 감소
			if (in_degree[u] == 0) push(&s, u);
			node = node->link;   // 다음 정점
		}
	}
	free(in_degree);
	printf("\n");
	return (i == g->n);	// 반환값이 1이면 성공, 0이면 실패
}

void set_vertex(GraphType* g, int n)
{
	g->n = n;
}

void delete_graph(GraphType* g)
{
	int i;
	for (i = 0; i < g->n; i++) {
		GraphNode* node = g->adj_list[i];
		while (node != NULL) {
			GraphNode* tmp = node;
			node = node->link;
			free(tmp);
		}
	}
}


int main(void)
{
	GraphType g;
	graph_init(&g);
	// test data 1
	
	set_vertex(&g, 6);
	insert_edge(&g, 0, 2);
	insert_edge(&g, 0, 3);
	insert_edge(&g, 1, 3);
	insert_edge(&g, 1, 4);
	insert_edge(&g, 2, 3);
	insert_edge(&g, 2, 5);
	insert_edge(&g, 3, 5);
	insert_edge(&g, 4, 5);
	
	/*
	// test data 2
	set_vertex(&g, 8);
	insert_edge(&g, 0, 1);
	insert_edge(&g, 1, 2);
	insert_edge(&g, 1, 3);
	insert_edge(&g, 1, 4);
	insert_edge(&g, 2, 7);
	insert_edge(&g, 3, 6);
	insert_edge(&g, 4, 5);
	insert_edge(&g, 4, 6);
	insert_edge(&g, 5, 7);
	insert_edge(&g, 6, 7);
	*/
	//위상 정렬 
	topo_sort(&g);
	// 동적 메모리 반환 코드 생략- 10 -
	delete_graph(&g);
	return 0;
}
#endif