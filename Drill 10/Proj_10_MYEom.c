#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define PROB 2

#if PROB == 1
typedef struct WORLD_COORDINATE {
	int x;
	int y;
	int z;
} element;

typedef struct STACKNODE {
	element data;
	struct STACKNODE* link;
} StackNode;

typedef struct {
	StackNode* top;
} LinkedlistStack;

int is_empty(LinkedlistStack* p)
{
	return (p->top == NULL);
}

int is_full(LinkedlistStack* p)
{
	return 0;
}

int init(LinkedlistStack* p)
{
	p->top = NULL;
}

void print_stack(LinkedlistStack* p)
{
	printf("----- 스택 내용 -----\n");
	if (is_empty(p)) {
		fprintf(stderr, "스택 공백 오류\n");
		return;
	}
	else {
		for (StackNode* s = p->top; s != NULL; s = s->link) {
			printf("(%d, %d, %d) ", s->data.x, s->data.y, s->data.z);
			if (s == p->top) 
				printf("<--- TOP \n");
			else printf("\n");
		}
	}
	printf("--------------------\n");
}

void push(LinkedlistStack* p, element item)
{
	StackNode* temp = (StackNode*)malloc(sizeof(StackNode));
	temp->data = item;
	temp->link = p->top;
	p->top = temp;
}

// pop 함수는 스택에서 원소를 꺼내고 버리는 작업에 적합하며
// peek 함수는 스택의 맨 위에 있는 원소를 확인하는 작업에 적합

element pop(LinkedlistStack* p)
{
	// 스택이 비어있을 경우에는 data 변수를 INT_MIN 값으로 초기화하여 반환하는 것이 적절
	element data = { INT_MIN, INT_MIN, INT_MIN };
	if (is_empty(p)) {
		printf("스택이 비어있음\n");
		return data;
	}
	else {
		StackNode* temp = p->top;  //스택의 top노드를 가리키는 포인터 변수
		data = temp->data; // temp의 data필드에 저장된 값을 data 변수에 복사 (스택에서 pop)
		p->top = p->top->link; // p->top을 temp->link로 바꿔서
		// 스택의 top이 이전 top의 바로 아래 노드를 가리키도록. pop한 노드를 제거
		free(temp); // 메모리 해제
		return data;
	}
}

int main(void)
{
	StackNode s;
	element item;

	init(&s);
	print_stack(&s);
	item.x = 1; item.y = 1; item.z = 1;
	printf("Push item\n");
	push(&s, item); print_stack(&s);
	item.x = 2; item.y = 2; item.z = 2;
	printf("Push item\n");
	push(&s, item); print_stack(&s);
	item.x = 3; item.y = 3; item.z = 3;
	printf("Push item\n");
	push(&s, item); print_stack(&s);
	item.x = 4; item.y = 4; item.z = 4;
	printf("Push item\n");
	push(&s, item); print_stack(&s);
	printf("PoP item\n");
	item = pop(&s);
	printf("PoP된 data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_stack(&s);
	printf("PoP item\n");
	item = pop(&s);
	printf("PoP된 data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_stack(&s);
	printf("PoP item\n");
	item = pop(&s);
	printf("PoP된 data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_stack(&s);
	printf("PoP item\n");
	item = pop(&s);
	printf("PoP된 data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_stack(&s);
	printf("PoP item\n");
	item = pop(&s);
	printf("PoP data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_stack(&s);
	printf("PoP item\n");
	item = pop(&s);
	printf("PoP된 data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_stack(&s);
	
	return 0;
}

#elif PROB == 2

typedef struct WORLD_COORDINATE {
	int x;
	int y;
	int z;
}element; 

typedef struct QueueNode {
	element data;
	struct QueueNode* link;
} QueueNode;

typedef struct {		
	QueueNode* front, * rear;
} LinkedQueue;

void init(LinkedQueue* q)
{
	q->front = q->rear = NULL;
}

int is_empty(LinkedQueue* q)
{
	return (q->front == NULL);
}

int is_full(LinkedQueue* q)
{
	return 0; 
}

void enqueue(LinkedQueue* q, element data)
{
	QueueNode* temp = (QueueNode*)malloc(sizeof(QueueNode));
	temp->data = data; 		
	temp->link = NULL; 		
	if (is_empty(q)) { 		
		q->front = temp;
		q->rear = temp;
	}
	else { 		
		q->rear->link = temp;  
		q->rear = temp;
	}
}
// 삭제 함수
element dequeue(LinkedQueue* q)
{
	QueueNode* temp = q->front;
	element data = { INT_MIN, INT_MIN, INT_MIN };

	if (is_empty(q)) {	
		fprintf(stderr, "큐가 비어있음\n");
		return data;
	}
	else { 
		data = temp->data; 		
		q->front = q->front->link; 
		if (q->front == NULL) 	
			q->rear = NULL;
		free(temp); 			
		return data; 			
	}
}

void print_queue(LinkedQueue* q)
{
	QueueNode* p;

	printf("====== 큐 ====== \n");
	if (q->front == NULL && q->rear == NULL)
		printf("( NULL ) <--- Front, Rear \n");
	else {
		for (p = q->front; p != NULL; p = p->link) {
			printf("(%d, %d, %d) ", p->data.x, p->data.y, p->data.z);
			if (p == q->front && p == q->rear) printf("<--- Front, Rear \n");
			else if (p == q->front) printf("<--- Front \n");
			else if (p == q->rear) printf("<--- Rear \n");
			else printf("\n");
		}
	}
	printf("============== \n");
}

int main(void)
{
	LinkedQueue queue;
	element item;

	init(&queue); // 큐 초기화
	print_queue(&queue);
	printf("enqueue item \n");
	item.x = 1, item.y = 1, item.z = 1;
	enqueue(&queue, item); print_queue(&queue);
	printf("enqueue item \n");
	item.x = 2, item.y = 2, item.z = 2;
	enqueue(&queue, item); print_queue(&queue);
	printf("enqueue item \n");
	item.x = 3, item.y = 3, item.z = 3;
	enqueue(&queue, item); print_queue(&queue);
	printf("enqueue item \n");
	item.x = 4, item.y = 4, item.z = 4;
	enqueue(&queue, item); print_queue(&queue);
	printf("enqueue item \n");
	item.x = 5, item.y = 5, item.z = 5;
	enqueue(&queue, item); print_queue(&queue);
	printf("dequeue item\n");
	item = dequeue(&queue);
	printf("Dequeue된 data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_queue(&queue);
	printf("dequeue item\n");
	item = dequeue(&queue);
	printf("Dequeue된 data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_queue(&queue);
	printf("dequeue item\n");
	item = dequeue(&queue);
	printf("Dequeue된 data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_queue(&queue);
	printf("dequeue item\n");
	item = dequeue(&queue);
	printf("Dequeue된 data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_queue(&queue);
	printf("dequeue item\n");
	item = dequeue(&queue);
	printf("Dequeue된 data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_queue(&queue);
	printf("dequeue item\n");
	item = dequeue(&queue);
	printf("Dequeue된 data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_queue(&queue);

	return 0;
}
#endif