#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define SIZE 100
#define MAX_SIZE 50000
#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t) )
#define MAX_ELEMENT 20000
#define BUCKETS 10
#define DIGITS 5  //최대 자리수

typedef struct {
	int key;
}element;
typedef struct {
	element heap[MAX_ELEMENT];
	int heap_size;
}HeapType;

typedef int qelement;
typedef struct {
	qelement data[SIZE];
	int front, rear;
}QueueType;

//선택정렬
void selection_sort(int list[], int n)
{
	int i, j, least, temp;
	for (i = 0; i < n - 1; i++) {
		least = i;
		for (j = i + 1; j < n; j++)
			if (list[j] < list[least]) least = j;
		SWAP(list[i], list[least], temp);
	}
}

//삽입정렬
void insertion_sort(int list[], int n)
{
	int i, j, key;
	for (i = 1; i < n; i++) {
		key = list[i];
		for (j = i - 1; j >= 0 && list[j] > key; j--)
			list[j + 1] = list[j];
		list[j + 1] = key;
	}
}

//버블정렬
void bubble_sort(int list[], int n)
{
	int i, j, temp;
	for (i = n - 1; i > 0; i--) {
		for (j = 0; j < i; j++)
			if (list[j] > list[j + 1])
				SWAP(list[j], list[j + 1], temp);
	}
}

//셸 정렬
void inc_insertion_sort(int list[], int first, int last, int gap)
{
	int i, j, key;
	for (i = first + gap; i <= last; i = i + gap) {
		key = list[i];
		for (j = i - gap; j >= first && key < list[j]; j = j - gap)
			list[j + gap] = list[j];
		list[j + gap] = key;
	}
}

void shell_sort(int list[], int n)
{
	int i, gap;
	for (gap = n / 2; gap > 0; gap = gap / 2) {
		if ((gap % 2) == 0) gap++;
		for (i = 0; i < gap; i++)
			inc_insertion_sort(list, i, n - 1, gap);
	}
}

//퀵 정렬
int partition(int list[], int left, int right) {
	int pivot, temp;
	int low, high;

	low = left;
	high = right + 1;
	pivot = list[left];
	do {
		do
			low++;
		while (low <= right && list[low] < pivot);
		do
			high--;
		while (high >= left && list[high] > pivot);
		if (low < high) SWAP(list[low], list[high], temp);
	} while (low < high);

	SWAP(list[left], list[high], temp);
	return high;
}

void quick_sort(int list[], int left, int right)
{
	if (left < right) {
		int q = partition(list, left, right);
		quick_sort(list, left, q - 1);
		quick_sort(list, q + 1, right);
	}
}
//합병정렬
int sorted[SIZE];
void merge(int list[], int left, int mid, int right) {
	int i, j, k, l;
	i = left; j = mid + 1; k = left;

	while (i <= mid && j <= right) {
		if (list[i] <= list[j])
			sorted[k++] = list[i++];
		else
			sorted[k++] = list[j++];
	}

	if (i > mid)
		for (l = i; l <= right; l++)
			sorted[k++] = list[l];
	else
		for (l = i; l <= mid; l++)
			sorted[k++] = list[l];

	for (l = left; l <= right; l++)
		list[l] = sorted[l];
}

void merge_sort(int list[], int left, int right) {
	int mid;
	if (left < right) {
		mid = (left + right) / 2;
		merge_sort(list, left, mid);
		merge_sort(list, mid + 1, right);
		merge(list, left, mid, right);
	}
}

//힙정렬
HeapType* create() {
	HeapType* h = (HeapType*)malloc(sizeof(HeapType));
	return h;
}

void init(HeapType* h) {
	h->heap_size = 0;
}

void insert_max_heap(HeapType* h, element item) {
	int i = ++(h->heap_size);

	while ((i != 1) && (item.key > h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;
}

element delete_max_heap(HeapType* h) {
	int parent, child;
	element item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;

	while (child <= h->heap_size) {
		if ((child < h->heap_size) && (h->heap[child].key) < h->heap[child + 1].key)
			child++;
		if (temp.key >= h->heap[child].key) break;
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

void heap_sort(element a[], int n) {
	int i;
	HeapType* h;

	h = create();
	init(h);
	for (i = 0; i < n; i++) {
		insert_max_heap(h, a[i]);
	}
	for (i = (n - 1); i >= 0; i--) {
		a[i] = delete_max_heap(h);
	}
	free(h);
}

//기수정렬
void error(char* message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void init_queue(QueueType* q) {
	q->front = q->rear = 0;
}

int is_empty(QueueType* q) {
	return (q->front == q->rear);
}

int is_full(QueueType* q) {
	return ((q->rear + 1) % SIZE == q->front);
}

void enqueue(QueueType* q, qelement item) {
	if (is_full(q)) {
		fprintf(stderr, "큐가 포화상태입니다.\n");
		exit(1);
	}
	q->rear = (q->rear + 1) % SIZE;
	q->data[q->rear] = item;
}

qelement dequeue(QueueType* q) {
	if (is_empty(q)) {
		fprintf(stderr, "큐가 공백상태입니다.\n");
		exit(1);
	}
	q->front = (q->front + 1) % SIZE;
	return q->data[q->front];
}

void radix_sort(int list[], int n)
{
	int i, b, d, factor = 1;
	QueueType queues[BUCKETS];

	for (b = 0; b < BUCKETS; b++) 
		init_queue(&queues[b]);	// 큐들의 초기화

	for (d = 0; d < DIGITS; d++) {
		for (i = 0; i < n; i++) {
			int digit = (list[i] / factor) % 10;
			enqueue(&queues[digit], list[i]); // 데이터들을 자리수에 따라 큐에 삽입
		}

		for (b = i = 0; b < BUCKETS; b++) {
			while (!is_empty(&queues[b])) {
				list[i++] = dequeue(&queues[b]); // 버킷에서 추출하여 리스트로 합침
			}
		}

		factor *= 10; // 그 다음 자리수로 간다.
	}
}

int main(void)
{
	int i, s_time, e_time;
	int* data = (int*)malloc(sizeof(int) * SIZE); // 각 정렬을 동일한 데이터로 테스트하기 위한 원데이터
	int* list = (int*)malloc(sizeof(int) * SIZE); // 원데이터 -> 정렬된 데이터
	int* sorted = (int*)malloc(sizeof(int) * SIZE); //병합정렬을 위한 추가 메모리로 글로벌변수로 선언
		if (data == NULL || list == NULL || sorted == NULL) {
			printf("데이터 저장을 위한 메모리 할당 오류\n"); exit(-1);
		}

	printf("정렬 기법 비교 \n");
	printf("Data 크기 : %d \n\n", SIZE);
	srand(100);
	for (i = 0; i < SIZE; i++) // 난수 생성 및 출력
		data[i] = rand(); // 난수 발생
	memcpy(list, data, sizeof(int) * SIZE);

	s_time = clock();
	selection_sort(list, SIZE); // 선택정렬 호출
	e_time = clock();

	printf("선택정렬 시간 : %d\n", e_time - s_time);
	if (SIZE <= 100) {
		for (i = 0; i < SIZE; i++)
			printf("%d ", list[i]);
		printf("\n\n");
	}

	memcpy(list, data, sizeof(int) * SIZE);
	s_time = clock();
	insertion_sort(list, SIZE);
	e_time = clock();
	printf("삽입정렬 시간 : %d\n", e_time - s_time);
	if (SIZE <= 100) {
		for (i = 0; i < SIZE; i++)
			printf("%d ", list[i]);
		printf("\n\n");
	}

	memcpy(list, data, sizeof(int) * SIZE);
	s_time = clock();
	bubble_sort(list, SIZE);
	e_time = clock();
	printf("버블정렬 시간 : %d\n", e_time - s_time);
	if (SIZE <= 100) {
		for (i = 0; i < SIZE; i++)
			printf("%d ", list[i]);
		printf("\n\n");
	}

	memcpy(list, data, sizeof(int) * SIZE);
	s_time = clock();
	shell_sort(list, SIZE);
	e_time = clock();
	printf("셸정렬 시간 : %d\n", e_time - s_time);
	if (SIZE <= 100) {
		for (i = 0; i < SIZE; i++)
			printf("%d ", list[i]);
		printf("\n\n");
	}

	memcpy(list, data, sizeof(int) * SIZE);
	s_time = clock();
	merge_sort(list, 0, SIZE - 1);
	e_time = clock();
	printf("병합정렬 시간 : %d\n", e_time - s_time);
	if (SIZE <= 100) {
		for (i = 0; i < SIZE; i++)
			printf("%d ", list[i]);
		printf("\n\n");
	}

	memcpy(list, data, sizeof(int) * SIZE);
	s_time = clock();
	quick_sort(list, 0, SIZE - 1);
	e_time = clock();
	printf("퀵정렬 시간 : %d\n", e_time - s_time);
	if (SIZE <= 100) {
		for (i = 0; i < SIZE; i++)
			printf("%d ", list[i]);
		printf("\n\n");
	}

	memcpy(list, data, sizeof(int) * SIZE);
	s_time = clock();
	heap_sort(list, SIZE);
	e_time = clock();
	printf("힙정렬 시간 : %d\n", e_time - s_time);
	if (SIZE <= 100) {
		for (i = 0; i < SIZE; i++)
			printf("%d ", list[i]);
		printf("\n\n");
	}

	memcpy(list, data, sizeof(int) * SIZE);
	s_time = clock();
	radix_sort(list, SIZE); // 기수정렬 호출
	e_time = clock();
	printf("기수정렬 시간 : %d\n", e_time - s_time);
	if (SIZE <= 100) {
		for (i = 0; i < SIZE; i++)
			printf("%d ", list[i]);
		printf("\n\n");
	}
	free(data); free(list); free(sorted);
	return 0;
}