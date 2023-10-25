#include <stdio.h>
#include <stdlib.h>

#define _CRT_SECURE_NO_WARNINGS
#define PROB 2

#if PROB == 1
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 50
int visited[MAX_VERTICES];
#define MAX_QUEUE_SIZE 10

typedef struct GraphType {
	int n; // 정점의 개수
	int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;

// 큐
typedef int element;
typedef struct { 
	element  queue[MAX_QUEUE_SIZE];
	int  front, rear;
} QueueType;

void error(const char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void queue_init(QueueType* q)
{
	q->front = q->rear = 0;
}

int is_empty(QueueType* q)
{
	return (q->front == q->rear);
}

int is_full(QueueType* q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

void enqueue(QueueType* q, element item)
{
	if (is_full(q))
		error("큐가 포화상태입니다");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->queue[q->rear] = item;
}

element dequeue(QueueType* q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->queue[q->front];
}

// 그래프
void init(GraphType* g)
{
	int r, c;
	g->n = 0;
	for (r = 0; r < MAX_VERTICES; r++)
		for (c = 0; c < MAX_VERTICES; c++)
			g->adj_mat[r][c] = 0;
}

// 정점 삽입 연산
void insert_vertex(GraphType* g, int v)
{
	if (((g->n) + 1) > MAX_VERTICES) {
		fprintf(stderr, "그래프: 정점의 개수 초과");
		return;
	}
	g->n++;
}

// 정점 갯수
void set_vertex(GraphType* g, int n)
{
	g->n = n;
	if (g->n > MAX_VERTICES)
		printf("정점의 개수 초과");
	return;
}

// 간선 삽입 연산
void insert_edge(GraphType* g, int start, int end)
{
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "그래프: 정점 번호 오류");
		return;
	}
	g->adj_mat[start][end] = 1;
	g->adj_mat[end][start] = 1;
}

void dfs_mat(GraphType* g, int v, int visited[])
{
	int w;
	visited[v] = TRUE; // 정점 v의 방문 표시
	printf("[ %d ] -> ", v); // 방문한 정점 출력
	for (w = 0; w < g->n; w++) // 인접 정점 탐색
		if (g->adj_mat[v][w] && !visited[w])
			dfs_mat(g, w, visited); //정점 w에서 DFS 새로 시작
}

void bfs_mat(GraphType* g, int v, int visited[])
{
	int w;
	QueueType q;
	queue_init(&q); // 큐 초기화
	visited[v] = TRUE; // 정점 v 방문 표시
	printf("[ %d ] -> ", v);
	enqueue(&q, v); // 시작 정점을 큐에 저장
	while (!is_empty(&q)) {
		v = dequeue(&q); // 큐에 정점 추출
		for (w = 0; w < g->n; w++) // 인접 정점 탐색
			if (g->adj_mat[v][w] && !visited[w]) {
				visited[w] = TRUE; // 방문 표시
				printf(" [ %d ] -> ", w);
				enqueue(&q, w); // 방문한 정점을 큐에 저장
			}
	}
}

void printf_graph_matrix(GraphType* g) 
{
	printf("   |");
	for (int i = 0; i < g->n; i++) {
		printf("%d ", i);
	}
	printf("\n-------------------------");
	printf("\n");

	for (int i = 0; i < g->n; i++) {
		printf(" %d |", i);
		for (int j = 0; j < g->n; j++) {
			printf("%d ", g->adj_mat[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}


int main(void)
{
	GraphType* g;
	int i;
	int visited[MAX_VERTICES];
	g = (GraphType*)malloc(sizeof(GraphType));
	init(g);

	//그래프 초기화 및 간선 추가
	set_vertex(g, 11);
	insert_edge(g, 0, 1);
	insert_edge(g, 0, 2);
	insert_edge(g, 0, 3);
	insert_edge(g, 1, 2);
	insert_edge(g, 1, 3);
	insert_edge(g, 2, 3);
	insert_edge(g, 2, 4);
	insert_edge(g, 4, 5);
	insert_edge(g, 4, 7);
	insert_edge(g, 4, 8);
	insert_edge(g, 5, 6);
	insert_edge(g, 6, 7);
	insert_edge(g, 6, 10);
	insert_edge(g, 7, 9);
	insert_edge(g, 7, 10);
	insert_edge(g, 8, 9);

	//print matrix of graph
	printf_graph_matrix(g);

	//깊이 우선 탐색
	for (i = 0; i < MAX_VERTICES; i++) visited[i] = 0;
	printf("깊이 우선 탐색\n");
	dfs_mat(g, 0, visited);
	printf("\n\n");

	//너비 우선 탐색
	for (i = 0; i < MAX_VERTICES; i++) visited[i] = 0;
	printf("너비 우선 탐색\n");
	bfs_mat(g, 0, visited);
	printf("\n");
	free(g);
	return 0;
}

#elif PROB == 2

#define MAX_VERTICES 50
int visited[MAX_VERTICES];
#define TRUE 1
typedef struct GraphNode
{
	int vertex;
	struct GraphNode* link;
} GraphNode;

typedef struct GraphType {
	int n; // 정점의 개수
	GraphNode* adj_list[MAX_VERTICES];
} GraphType;


// 큐
#define MAX_QUEUE_SIZE 10
typedef int element;
typedef struct { 
	element  queue[MAX_QUEUE_SIZE];
	int  front, rear;
} QueueType;

void error(const char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void queue_init(QueueType* q)
{
	q->front = q->rear = 0;
}

int is_empty(QueueType* q)
{
	return (q->front == q->rear);
}

int is_full(QueueType* q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

// 삽입 함수
void enqueue(QueueType* q, element item)
{
	if (is_full(q))
		error("큐가 포화상태입니다");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->queue[q->rear] = item;
}

// 삭제 함수
element dequeue(QueueType* q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->queue[q->front];
}

//그래프
void init(GraphType* g)
{
	int v;
	g->n = 0;
	for (v = 0; v < MAX_VERTICES; v++)
		g->adj_list[v] = NULL;
}

void insert_vertex(GraphType* g, int v)
{
	if (((g->n) + 1) > MAX_VERTICES) {
		fprintf(stderr, "그래프: 정점의 개수 초과");
		return;
	}
	g->n++;
}

void set_vertex(GraphType* g, int num)
{
	g->n = num;
	if (g->n > MAX_VERTICES)
		printf("그래프: 정점의 개수 초과");
	return;
}

void insert_edge(GraphType* g, int u, int v)
{
	GraphNode* node;
	if (u >= g->n || v >= g->n) {
		fprintf(stderr, "그래프: 정점 번호 오류");
		return;
	}
	node = (GraphNode*)malloc(sizeof(GraphNode));
	node->vertex = v;
	node->link = g->adj_list[u]; //연결리스트의 앞쪽에 삽입
	g->adj_list[u] = node;
}

void print_adj_list(GraphType* g)
{
	for (int i = 0; i < g->n; i++) {
		GraphNode* p = g->adj_list[i];
		printf("정점 %d의 인접 리스트 ", i);
		while (p != NULL) {
			printf("-> %d ", p->vertex);
			p = p->link;
		}
		if (p == NULL)
			printf("-> NULL");
		printf("\n");
	}
	printf("\n");
}

void dfs_list(GraphType* g, int v, int visited[])
{
	GraphNode* w;
	visited[v] = TRUE; // 정점 v의 방문 표시
	printf("[ %d ] -> ", v); // 방문한 정점 출력
	for (w = g->adj_list[v]; w; w = w->link)// 인접 정점 탐색
		if (!visited[w->vertex])
			dfs_list(g, w->vertex, visited); //정점 w에서 DFS 새로 시작
}

void bfs_list(GraphType* g, int v, int visited[])
{
	GraphNode* w;
	QueueType q;
	queue_init(&q); // 큐 초기 화
	visited[v] = TRUE; // 정점 v 방문 표시
	printf("[ %d ] -> ", v);
	enqueue(&q, v); // 시작정점을 큐에 저장
	while (!is_empty(&q)) {
		v = dequeue(&q); // 큐에 저장된 정점 선택
		for (w = g->adj_list[v]; w; w = w->link) //인접 정점 탐색
			if (!visited[w->vertex]) { // 미방문 정점 탐색
				visited[w->vertex] = TRUE; // 방문 표시
				printf("[ %d ] -> ", w->vertex);
				enqueue(&q, w->vertex); //정점을 큐에삽입
			}
	}
}

int main(void)
{
	GraphType* g;
	int i;
	int visited[MAX_VERTICES];
	g = (GraphType*)malloc(sizeof(GraphType));
	init(g);

	//그래프 초기화 및 간선 추가
	set_vertex(g, 11);
	insert_edge(g, 0, 1);
	insert_edge(g, 0, 2);
	insert_edge(g, 0, 3);
	insert_edge(g, 1, 2);
	insert_edge(g, 1, 3);
	insert_edge(g, 2, 3);
	insert_edge(g, 2, 4);
	insert_edge(g, 4, 5);
	insert_edge(g, 4, 7);
	insert_edge(g, 4, 8);
	insert_edge(g, 5, 6);
	insert_edge(g, 6, 7);
	insert_edge(g, 6, 10);
	insert_edge(g, 7, 9);
	insert_edge(g, 7, 10);
	insert_edge(g, 8, 9);

	// 그래프 출력
	print_adj_list(g);

	// 깊이 우선 탐색
	for (i = 0; i < MAX_VERTICES; i++) visited[i] = 0;
	printf("깊이 우선 탐색\n");
	dfs_list(g, 0, visited);
	printf("\n\n");

	// 너비 우선 탐색
	for (i = 0; i < MAX_VERTICES; i++) visited[i] = 0;
	printf("너비 우선 탐색\n");
	bfs_list(g, 0, visited);
	printf("\n");
	free(g);
	return 0;
}

#endif