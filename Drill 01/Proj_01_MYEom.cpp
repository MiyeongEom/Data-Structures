#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node {
	int data;
	struct node* next;
}NODE;

NODE* head = NULL;

void insert(int input);
void print();
void Clear(NODE** head);

int main() {

	int data =0;
	int temp = 0;
	clock_t start, stop;
	double duration;

	srand(30);
	printf("rand�Լ��� seed �� : 1234567\n");

	printf("Data Size : ");
	scanf_s("%d", &data);
	int* a = (int*)malloc(sizeof(int) * data);

	start = clock();
	for (int i = 0; i < data; i++) {
		a[i] = rand();

		if (i >= 1) {
			for (int j = 0; j < data; j++) {
				if (a[i] < a[j]) {
					temp = a[i];
					a[i] = a[j];
					a[j] = temp;
				}
			}
		}
	}
	stop = clock();
	duration = (double)(stop - start) / CLOCKS_PER_SEC;
	printf("�迭�� �̿��� ����ð��� %f���Դϴ�.\n", duration);

	//for (int i = 0; i < data; i++) {
	//	printf("%d\t", a[i]);
	//}

	printf("\n\n");
	// ------------------ ���Ḯ��Ʈ -----------------------------

	NODE* head;
	double duration2;
	srand(1234567);
	start = clock();

	for (int i = 0; i < data; i++) {
		int input = rand();
		insert(input);
	}

	stop = clock();
	duration2 = (double)(stop - start) / CLOCKS_PER_SEC;
	printf("���Ḯ��Ʈ�� �̿��� ����ð��� %f���Դϴ�.\n", duration2);
	//print();

	free(a);
	return 0;
}

void insert(int input) {
	NODE* newnode, * p;
	newnode = (NODE*)malloc(sizeof(NODE));

	if (newnode == NULL) {
		printf("�޸� �Ҵ� ����\n");
		return;
	}

	if (newnode) {
		newnode->next = NULL;
		newnode->data = input;

		p = head;

		if (head == NULL) {
			head = newnode;
		}

		else if (head->data > newnode->data) {
			newnode->next = head;
			head = newnode;
			return;
		}

		else
		{
			while (p->next != NULL) {
				if (p->next->data > newnode->data) {
					newnode->next = p->next;
					p->next = newnode;
					return;
				}
				p = p->next;
			}
		}

		if (p != 0) {
			p->next = newnode;
		}
	}
}

void print() {
	NODE* p;
	p = head;
	while (p->next != NULL) {
		printf("%d\t", p->data);
		p = p->next;
	}
	printf("%d", p->data);
}

void Clear(NODE** head) {
	NODE* prev = NULL;
	NODE* p = *head;
	while (p){
		prev = p;
		p = p->next;
		free(prev);
	}
	*head = NULL;
}