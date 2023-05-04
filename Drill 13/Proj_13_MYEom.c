#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define PROB 1 // 각각의 문제를 구현하고 해당 문제 번호를 변경하여 테스트

#if PROB == 1

#define MAX_ELEMENT 10
typedef int element;
typedef struct {
	element heap[MAX_ELEMENT + 1];
	int heap_size;
}HeapType;


HeapType* create()
{
	return (HeapType*)malloc(sizeof(HeapType));
}

void init(HeapType* h)
{
	h->heap_size = 0;
}

void insert_max_heap(HeapType* h, element item)
{
	int i;
	i = ++(h->heap_size);

	while ((i != 1) && (item > h->heap[i / 2])) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;    
}

element delete_max_heap(HeapType* h)
{
	int parent, child;
	element item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		if ((child < h->heap_size) &&
			(h->heap[child]) < h->heap[child + 1])
			child++;
		if (temp >= h->heap[child]) break;
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

void heap_sort(element a[], element sorted_list[], int n)
{
	int i;
	HeapType* h;

	h = create();
	init(h);
	for (i = 0; i < n; i++) {
		insert_max_heap(h, a[i]);
	}

	for (i = (n - 1); i >= 0; i--) {
		sorted_list[i] = delete_max_heap(h);
	}
	free(h);
}

void selection_sort(element a[], element b[], int n)
{
	int i, j, min_idx, tmp;
	for (i = 0; i < n; i++) {
		min_idx = i;
		for (j = i + 1; j < n; j++) {
			if (a[j] < a[min_idx]) {
				min_idx = j;
			}
		}
		tmp = a[i];
		a[i] = a[min_idx];
		a[min_idx] = tmp;
	}
	memcpy(b, a, n * sizeof(int));
}

#define SIZE MAX_ELEMENT

int main(void)
{
	element* list, * sorted_list;
	int i, s_time, e_time;
	srand(100);
	list = (element*)malloc(sizeof(element) * SIZE);
	sorted_list = (element*)malloc(sizeof(element) * SIZE);
	for (i = 0; i < SIZE; i++) list[i] = rand();
	printf("정수형 데이터 %d개 정렬 \n", SIZE);
	if (SIZE < 100) {
		for (int i = 0; i < SIZE; i++) printf("%d ", list[i]);
		printf("\n\n");
	}
	s_time = clock();
	heap_sort(list, sorted_list, SIZE);
	e_time = clock();
	printf("Heap Sort 걸린 시간 : %d msec\n", e_time - s_time);
	if (SIZE < 100) {
		for (int i = 0; i < SIZE; i++) printf("%d ", sorted_list[i]);
		printf("\n\n");
	}
	s_time = clock();
	selection_sort(list, sorted_list, SIZE);
	e_time = clock();
	printf("Selection Sort 걸린 시간 : %d msec\n", e_time - s_time);
	if (SIZE < 100) {
		for (int i = 0; i < SIZE; i++) printf("%d ", sorted_list[i]);
		printf("\n");
	}
	return 0;
}


#elif PROB == 2
// 2번 문제를 해결하기 위한 프로그램 작성
#define MAX_ELEMENT 200
typedef struct TreeNode {
	int weight;
	char ch;
	struct TreeNode* left;
	struct TreeNode* right;
} TreeNode;
typedef TreeNode* element;
typedef struct {
	element heap[MAX_ELEMENT];
	int heap_size;
} HeapType;

HeapType* create()
{
	return (HeapType*)malloc(sizeof(HeapType));
}

void init(HeapType* h)
{
	h->heap_size = 0;
}

void insert_min_heap(HeapType* h, element item)
{
	int i;
	i = ++(h->heap_size);

	while ((i != 1) && (item->weight < h->heap[i / 2]->weight)) {

		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;
}

element delete_min_heap(HeapType* h)
{
	int parent, child;
	element item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		if ((child < h->heap_size) &&
			(h->heap[child]->weight) > h->heap[child + 1]->weight)
			child++;
		if (temp->weight < h->heap[child]->weight) break;
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

TreeNode* make_tree(TreeNode* left, TreeNode* right)
{
	TreeNode* node =(TreeNode*)malloc(sizeof(TreeNode));
	node->left = left;
	node->right = right;
	return node;
}

void destroy_tree(TreeNode* root)
{
	if (root == NULL) return;
	destroy_tree(root->left);
	destroy_tree(root->right);
	free(root);
}

int is_leaf(TreeNode* root)
{
	return !(root->left) && !(root->right);
}

void print_array(int codes[], int n)
{
	for (int i = 0; i < n; i++)
		printf("%d", codes[i]);
	printf("\n");
}

void print_codes(TreeNode* root, int codes[], int top)
{

	if (root->left) {
		codes[top] = 1;
		print_codes(root->left, codes, top + 1);
	}

	if (root->right) {
		codes[top] = 0;
		print_codes(root->right, codes, top + 1);
	}

	if (is_leaf(root)) {
		printf("%c: ", root->ch);
		print_array(codes, top);
	}
}

void huffman_decode(TreeNode* root, char codes[])
{
	TreeNode* p = root;
	int i = 0;
	printf("\n허프만 코드를 이용한 디코딩 :\n");
	printf("Decode %s \n", codes);
	while (codes[i] != NULL) {
		if (p->left == NULL && p->right == NULL) {
			printf(" ==> %c \n", p->ch);
			p = root;
		}
		else {
			printf("%c", codes[i]);
			if (codes[i] == '1') {
				p = p->left;
			}
			else {
				p = p->right;
			}
			i++;
		}
	}
	if (p->left == NULL && p->right == NULL) {
		printf(" ==> %c \n", p->ch);
		p = root;
	}
}

TreeNode* make_huffman_tree(int freq[], char ch_list[], int n)
{
	int i;
	TreeNode* node, * x;
	HeapType* heap;
	element e, e1, e2;
	int codes[100];
	int top = 0;

	heap = create();
	init(heap);
	for (i = 0; i < n; i++) {
		node = make_tree(NULL, NULL);
		//e.ch = 
		node->ch = ch_list[i];
		//e.key = 
		node->weight = freq[i];
		e = node;
		insert_min_heap(heap, e);
	}
	for (i = 1; i < n; i++) {
		e1 = delete_min_heap(heap);
		e2 = delete_min_heap(heap);
		x = make_tree(e1, e2);
		x->weight = e1->weight + e2->weight;
		e = x;
		printf("%d+%d->%d \n", e1->weight, e2->weight, e->weight);
		insert_min_heap(heap, e);
	}
	e = delete_min_heap(heap);
	printf("\n문자별 허프만 코드 \n ");
	print_codes(e, codes, top);
	free(heap);
	return e;
}

int main(void)
{
	char ch_list[] = { 's', 'i', 'n', 't', 'e' };
	int freq[] = { 4, 6, 8, 12, 15 };
	TreeNode* head;
	head = make_huffman_tree(freq, ch_list, 5);
	huffman_decode(head, "1110101010000101");
	destroy_tree(head);
	return 0;
}

#endif
