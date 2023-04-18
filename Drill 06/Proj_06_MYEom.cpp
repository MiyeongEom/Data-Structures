#define _CRT_SECURE_NO_WARNINGS
#define PROB 1
#include <stdio.h>
#include <stdlib.h>

#if PROB == 1

#define MAX_QUEUE_SIZE 10000

typedef struct {
	int n;
	int t;
}element;

typedef struct { 
	element  data[MAX_QUEUE_SIZE];
	int  front, rear;
} QueueType;

void error(const char* message)
{
	fprintf(stderr,"%s\n", message);
	exit(1);
}

void init_queue(QueueType* q)
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

void queue_print(QueueType* q)
{
	printf("QUEUE(front=%d rear=%d) = ", q->front, q->rear);
	if (!is_empty(q)) {
		int i = q->front;
		do {
			i = (i + 1) % (MAX_QUEUE_SIZE);
			printf("(%d, %d), ", q->data[i].n, q->data[i].t);
			if (i == q->rear)
				break;
		} while (i != q->front);
	}
	printf(" Size %d\n", ((q->rear + MAX_QUEUE_SIZE) - q->front) % MAX_QUEUE_SIZE);
}

void enqueue(QueueType* q, element item)
{
	if (is_full(q))
		error("ť�� ��ȭ�����Դϴ�");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

element dequeue(QueueType* q)
{
	if (is_empty(q))
		error("ť�� ��������Դϴ�");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

element peek(QueueType* q)
{
	if (is_empty(q))
		error("ť�� ��������Դϴ�");
	return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}

int main(void)
{
	QueueType q;
	element el, new_el;
	int n;
	int new_n[MAX_QUEUE_SIZE], idx, i, ct;

	init_queue(&q);

	printf("���� ���̷��� �� : ");
	scanf_s("%d", &n);

	el.n = 1; el.t = 0;	enqueue(&q, el); ct = 0, idx = 0;

	while (!is_empty(&q))
	{
		el = dequeue(&q);
		if (ct != el.t) { idx = 0; ct = el.t; }
		if (el.n == n) { 
			printf("%d ������ �Ǵ� �� �ʿ��� �ҿ� �ð� : %d\n", el.n, el.t);
			break;
		}
		else {
			if (el.n / 3 != 0) { 
				new_el.n = el.n / 3; new_el.t = el.t + 1;
				for (i = 0; i < idx; i++) {
					if (new_el.n == new_n[i]) break;
				}
				if (i == idx || !idx) {
					enqueue(&q, new_el);
					new_n[idx++] = new_el.n;
				}
			}

			if (el.n * 2 > 0) { 
				new_el.n = el.n * 2; new_el.t = el.t + 1;
				for (i = 0; i < idx; i++) {
					if (new_el.n == new_n[i]) break;
				}
				if (i == idx || !idx) {
					enqueue(&q, new_el);
					new_n[idx++] = new_el.n;
				}
			}

		}
	}
	return 0;
}


#elif PROB == 2
#define MAX_QUEUE_SIZE 10000

typedef int element;

typedef struct {
	element  data[MAX_QUEUE_SIZE];
	int  front, rear;
} QueueType;

void error(const char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void init_queue(QueueType* q)
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

void queue_print(QueueType* q)
{
	printf("QUEUE(front=%d rear=%d) = ", q->front, q->rear);
	if (!is_empty(q)) {
		int i = q->front;
		do {
			i = (i + 1) % (MAX_QUEUE_SIZE);
			printf_s("(%d, %d), ", q->data[i]);
			if (i == q->rear)
				break;
		} while (i != q->front);
	}
	printf(" Size %d\n", ((q->rear + MAX_QUEUE_SIZE) - q->front) % MAX_QUEUE_SIZE);
}

void enqueue(QueueType* q, element item)
{
	if (is_full(q))
		error("ť�� ��ȭ�����Դϴ�");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

element dequeue(QueueType* q)
{
	if (is_empty(q))
		error("ť�� ��������Դϴ�");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

element peek(QueueType* q)
{
	if (is_empty(q))
		error("ť�� ��������Դϴ�");
	return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}

int main(void)
{
	int n, k;
	int i, j;
	QueueType q;

	printf("���ӿ� �����ϴ� ����� �� n�� �����ϴ� k �� :");
	scanf_s("%d %d", &n, &k);

	init_queue(&q);
	for (i = 1; i <= n; i++)
		enqueue(&q, i);

	printf("���� ��ȣ : ");
	while (!is_empty(&q)) {
		//k-1��°
		for (i = 0; i < k - 1; i++)
			enqueue(&q, dequeue(&q));
		//k��° ���
		j = dequeue(&q);
		printf(" %d ", j);
	}
	printf("\n���� ��Ƴ��� ����� %d ��ġ�� ���� �� �����\n", j);
	return 0;
}


#elif PROB == 3

#define MAX_QUEUE_SIZE 1000

typedef int element;

typedef struct {
	element  data[MAX_QUEUE_SIZE];
	int  front, rear;
} Queue;

void qerror(const char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void init_queue(Queue* q)
{
	q->front = q->rear = 0;
}

int is_qempty(Queue* q)
{
	return (q->front == q->rear);
}

int is_qfull(Queue* q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

void queue_print(Queue* q)
{
	printf("QUEUE(front=%d rear=%d) = ", q->front, q->rear);
	if (!is_qempty(q)) {
		int i = q->front;
		do {
			i = (i + 1) % (MAX_QUEUE_SIZE);
			printf("%d, ", q->data[i]);
			if (i == q->rear)
				break;
		} while (i != q->front);
	}
	printf(" Size %d\n", ((q->rear + MAX_QUEUE_SIZE) - q->front) % MAX_QUEUE_SIZE);
}

void enqueue(Queue* q, element item)
{
	if (is_qfull(q))
		qerror("ť�� ��ȭ�����Դϴ�");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

element dequeue(Queue* q)
{
	if (is_qempty(q))
		qerror("ť�� ��������Դϴ�");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

element qpeek(Queue* q)
{
	if (is_qempty(q)) {
		printf("ť�� ��������Դϴ�");
		return MAX_QUEUE_SIZE; //ť�� �ִ밪�� �־� �����Ͱ� ������ Ȯ��
	}
	return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}

#define MAX_STACK_SIZE 100

typedef int element;
typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
} Stack;

void init_stack(Stack* s)
{
	s->top = -1;
}

int is_sempty(Stack* s)
{
	return (s->top == -1);
}

int is_sfull(Stack* s)
{
	return (s->top == (MAX_STACK_SIZE - 1));
}

void push(Stack* s, element item)
{
	if (is_sfull(s)) {
		fprintf(stderr, "���� ��ȭ ����\n");
		return;
	}
	else s->data[++(s->top)] = item;
}

element pop(Stack* s)
{
	if (is_sempty(s)) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}
	else return s->data[(s->top)--];
}

element speek(Stack* s)
{
	if (is_sempty(s)) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}
	else return s->data[s->top];
}

int main(void)
{
	int n = 10;
	int number[MAX_QUEUE_SIZE] = { 3, 4, 6, 7, 8, 5, 9, 2, 1, 10};
	int i, result = 0;
	element sel;
	Queue LQ, RQ;
	Stack MS;

	init_queue(&LQ);
	init_queue(&RQ);
	init_stack(&MS);

	for (i = 1; i <= n; i++) 
		enqueue(&RQ, i);

	i = 0; result = 1;
	while (i != n) {
		sel = qpeek(&RQ);
		if (sel == number[i]) {
			enqueue(&LQ, dequeue(&RQ));
		}
		else if (sel < number[i]) {
			push(&MS, dequeue(&RQ));
			continue;
		}
		else {
			if (speek(&MS) == number[i]) {
				enqueue(&LQ, pop(&MS));
			}
			else {
				result = 0;
				break;
			}
		}
		i++;
	}

	printf("%d���� �׽�Ʈ ���� \n", n);

	for (i = 0; i < n; i++)
		printf("%d ", number[i]);
	if (result == 1)
		printf("\n�������� ���� : ����\n");
	else 
		printf("\n�������� ���� : �Ұ���\n");
}

#endif