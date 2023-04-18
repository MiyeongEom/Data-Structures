#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#define PROB 2

#if PROB == 1
#define MAX_LIST_SIZE 100

typedef int element;
typedef struct{
	element* array;
	int size;
} Array;

void error(const char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void init(Array* L)
{
	L->array = (element*)malloc(sizeof(element) * MAX_LIST_SIZE);
	if (L->array == NULL) {
		error("메모리 할당 오류");
	}
	L->size = 0;
}

int is_empty(Array* L)
{
	return L->size == 0;
}

int is_full(Array * L)
{
	return L->size == MAX_LIST_SIZE;
}

int add(Array* L, element item)
{
	int i;
	if (is_full(L)) {
		printf("리스트가 가득찼습니다. \n");
		return -1;
	}
	else {
		for (i = 0; i < L->size; i++) { 
			if (L->array[i] >= item) {
				for (int j = L->size; j > i; j--)
					L->array[j] = L->array[j - 1];
				L->array[i] = item;
				L->size++;
				return i;
			}
		}
		L->array[i] = item; L->size++; 
			return i;
	}
}

void display(Array* L)
{
	for (int i = 0; i < L->size; i++)
		printf("%d->", L->array[i]);
	printf("\n");
}

int get_length(Array* L)
{
	return L->size;
}

element get_entry(Array* L, int pos)
{
	if (pos < 0 || pos >= L->size)
		error("위치 오류");
	return L->array[pos];
}

int is_in_list(Array* L, element item)
{
	for (int i = 0; i < L->size; i++)
		if (L->array[i] == item) 
			return i;
	return -1;
}

int delete(Array* L, element item) 
{
	int i, j;
	int count = 0;
	for (i = 0; i < L->size; i++) {
		if (L->array[i] == item) {
			for (j = i + 1; j < L->size; j++)
				L->array[j - 1] = L->array[j];
			L->size--;
			return i;
		}
	}
	return -1;
}

void clear(Array* L)
{
	L->size = 0;
}

void array_free(Array* L)
{
	free(L->array);
	L->array = NULL;
	L->size = 0;
}

int main(void) {
	Array list;
	int item;
	char ch;

	init(&list);
	srand(100); 

	while (1) {
		item = rand();
		add(&list, item);
		display(&list);
		ch = getch();
		if (ch == 'q') break;
	}

	printf("get_length : %d \n", get_length(&list));
	printf("is_empty : %d, is_full : %d \n",
		is_empty(&list), is_full(&list));
	printf("get_entry : %d위치의 데이터는 %d\n", 5, get_entry(&list, 5));
	printf("is_in_list : %d의 위치는 %d \n", 5415, is_in_list(&list, 5415));
	printf("is_in_list : %d의 위치는 %d \n", 10, is_in_list(&list, 10));
	printf("delete : %d의 위치는 %d \n", 5415, delete(&list, 5415));
	display(&list);
	printf("call clear\n");
	clear(&list);
	display(&list);
	printf("리스트 길이 %d \n", get_length(&list));

	array_free(&list);
	return 0;
}


#elif PROB == 2

#define MAX_LIST_SIZE 100

typedef int element;

typedef struct NODE {
	element data;
	struct NODE* link;
}node;

typedef struct {
	node* list;
	int size;
} SortedList;

void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void init(SortedList* L)
{
	L->list = NULL;
	L->size = 0;
}

int is_empty(SortedList* L)
{
	return L->size == 0;
}

int is_full(SortedList* L)
{
	return L->size == MAX_LIST_SIZE;
}

void add(SortedList* L, element item)
{
	node* p = L->list;
	node* q = p;
	node* new_node;

	if (is_full(L)) {
		error("리스트가 가득찼습니다.");
	}
	else {
		new_node = (node*)malloc(sizeof(node));
		if (new_node == NULL) { printf("메모리 할당 오류 \n"); 
		return;
		}

		new_node->data = item;
		new_node->link = NULL;
		L->size++;

		if (L->list == NULL) { L->list = new_node; } 
		else {
			while (p != NULL) {
				if (p->data > item) {
					new_node->link = p;
					if (p == L->list) L->list = new_node;
					else q->link = new_node;
					return;
				}
				q = p;
				p = p->link;
			}
			q->link = new_node; 
		}
	}
}

void display(SortedList* L)
{
	node* p = L->list;
	while (p != NULL) {
		printf("%d->", p->data);
		p = p->link;
	}
	printf("\n");
}

int get_length(SortedList* L)
{
	return L->size;
}

element get_entry(SortedList* L, int pos)
{
	node* p = L->list;
	int count = 0;

	if (pos < 0 || pos > L->size)
		error("위치 오류");

	while (p != NULL) {
		if (pos == count) 
			return p->data;
		p = p->link;
		count++;
	}
	return -1;
}

int is_in_list(SortedList* L, element item)
{
	node* p = L->list;
	int count = 0;

	while (p != NULL) {
		if (p->data == item) 
			return count;
		p = p->link;
		count++;
	}
	return -1;
}

int delete(SortedList* L, element item) 
{
	int pos = 0;
	node* p = L->list;
	node* q = p;

	if (L->list->data == item) {
		L->list = L->list->link;
		free(q);
		L->size--;
		return pos;
	}
	else { 
		while (p != NULL) {
			if (p->data == item) {
				q->link = p->link;
				free(p);
				L->size--;
				return pos;
			}
			q = p;
			p = p->link;
			pos++;
		}
	}
	return -1; 
}

void list_free(SortedList* L)
{
	L->size = 0;
	node* p = L->list;
	node* q;

	while (p != NULL) {
		q = p;
		p = p->link;
		free(q);
	}
	L->list = NULL;
}

void clear(SortedList* L) {
	list_free(L);
	L->size = 0;
	return;
}


int main(void) {
	SortedList list;
	int item;
	char ch;

	init(&list);
	srand(100); 
	while (1) {
		item = rand();
		add(&list, item);
		display(&list);
		ch = getch();
		if (ch == 'q') break;
	}
	printf("get_length : %d \n", get_length(&list));
	printf("is_empty : %d, is_full : %d \n",
		is_empty(&list), is_full(&list));
	printf("get_entry : %d위치의 데이터는 %d\n", 5, get_entry(&list, 5));
	printf("is_in_list : %d의 위치는 %d \n", 5415, is_in_list(&list, 5415));
	printf("is_in_list : %d의 위치는 %d \n", 10, is_in_list(&list, 10));
	printf("delete : %d의 위치는 %d \n", 5415, delete(&list, 5415));
	display(&list);
	printf("call clear\n");
	clear(&list);
	display(&list);
	printf("리스트 길이 %d \n", get_length(&list));

	list_free(&list);
	return 0;
}

#endif