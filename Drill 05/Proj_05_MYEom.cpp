#define _CRT_SECURE_NO_WARNINGS
#define PROB 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#if PROB == 1
#define MAX_STACK_SIZE 100

typedef union {
	char oper;
	int operand;
}element;		

#define MAX_STACK_SIZE 50

typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
} StackType;

void init_stack(StackType* s)
{
	s->top = -1;
}

int is_empty(StackType* s)
{
	return (s->top == -1);
}

int is_full(StackType* s)
{
	return (s->top == (MAX_STACK_SIZE - 1));
}

void push(StackType* s, element item)
{
	if (is_full(s)) {
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else {
		s->data[++(s->top)] = item;
	}
}

element pop(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->data[(s->top)--];
}

element peek(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->data[s->top];
}

int eval(char exp[])
{
	int op1, op2, idx;
	int i = 0;
	int result;
	int len = strlen(exp);
	char ch;
	StackType s;
	element value;

	char num[50];

	init_stack(&s);
	while (i < len) {
		ch = exp[i];
		if (ch == ' ') i++;
		else if (ch != '+' && ch != '-' && ch != '*' && ch != '/') {
			idx = 0;
			num[idx] = ch;
			while (isdigit(exp[++i]))
				num[++idx] = exp[i];
			num[++idx] = 0;
			value.operand = atoi(num);
			push(&s, value);
		}
		else {	
			op2 = pop(&s).operand;
			op1 = pop(&s).operand;
			switch (ch) { 
			case '*': value.operand = op1 * op2; push(&s, value); 
				break;
			case '/': value.operand = op1 / op2; push(&s, value); 
				break;
			case '+': value.operand = op1 + op2; push(&s, value); 
				break;
			case '-': value.operand = op1 - op2; push(&s, value); 
				break;
			}
			i++;
		}
	}
	result = pop(&s).operand;

	if (!is_empty(&s)) {
		printf("수식 오류\n");
		exit(-1); 
	}
	else return result;
}

int pre(char op)
{
	switch (op) {
	case '(': case ')': return 0;
	case '+': case '-': return 1;
	case '*': case '/': return 2;
	}
	return -1;
}


void postfix(const char exp[], char pexp[])
{
	char ch, top_op;
	element elem;
	int len = strlen(exp);
	StackType s;

	int i = 0, idx = 0;
	init_stack(&s);		

	for (i = 0; i < len; i++) {
		ch = exp[i];
		elem.oper = ch;
		switch (ch) {
		case '+': case '-': case '*': case '/':
			while (!is_empty(&s) && (pre(ch) <= pre(peek(&s).oper)))
				sprintf(&pexp[idx++], "%c", pop(&s).oper);
			push(&s, elem);
			sprintf(&pexp[idx++], " ");
			break;
		case '(':	
			push(&s, elem);
			break;
		case ')':	
			top_op = pop(&s).oper;
			while (top_op != '(') {
				sprintf(&pexp[idx++], "%c", top_op);
				top_op = pop(&s).oper;
			}
			break;
		default:		
			sprintf(&pexp[idx++], "%c", ch);
			break;
		}
	}
	while (!is_empty(&s))
		sprintf(&pexp[idx++], "%c", pop(&s).oper);
	pexp[idx] = 0;
}

int main(void)
{
	const char* s = "10 + 20 * (20+ 10) / 100 +5 -3";
	char pexp[100];
	int result;

	printf("중위표기 수식 : %s \n", s);
	postfix(s, pexp);

	printf("후위표기 수식 : %s \n", pexp);
	result = eval(pexp);

	printf("연산 결과 : %d \n", result);
	return 0;
}

#elif PROB == 2
/*
*	maze.c
*/

#define MAX_STACK_SIZE 50
#define MAZE_SIZE 6

#define true 1
#define false 0
#define EXIT_ROW 4
#define EXIT_COL 5

typedef struct{
	short r;
	short c;
	int dir;  //방향
} Object;

typedef struct STACK {
	Object  data[MAX_STACK_SIZE]; 
	int top; 
}stack;

typedef struct {
	short v;
	short h;
}offsets;

offsets move[4] = { {-1,0}, {0,1}, {1,0}, {0, -1} }; 
Object entry = { 1,0,0 }; //시작 [1]

char maze[MAZE_SIZE][MAZE_SIZE] = {
{'1', '1', '1', '1', '1', '1'},
{'e', '0', '1', '0', '0', '1'},
{'1', '0', '0', '0', '1', '1'},
{'1', '0', '1', '0', '1', '1'},
{'1', '0', '1', '0', '0', 'x'},
{'1', '1', '1', '1', '1', '1'},
};

void init_stack(stack* s)
{
	s->top = -1;
}

int is_Empty(stack* s)
{
	return (s->top == -1);
}

int is_Full(stack* s)
{
	return (s->top == (MAX_STACK_SIZE - 1));
}

void push(stack* s, Object item)
{
	if (is_Full(s)) {
		printf("stack is full\n");
	}
	else s->data[++(s->top)] = item;
}

Object pop(stack* s)
{
	if (is_Empty(s)) {
		printf("stack is empty\n");
	}
	else return s->data[(s->top)--];
}

Object peek(stack* s)
{
	if (is_Empty(s)) {
		printf("stack is empty\n");
	}
	else return s->data[s->top];
}


void maze_print(char maze[MAZE_SIZE][MAZE_SIZE])
{
	printf("\n");
	printf("[ -------- 미로 --------- ] \n");
	for (int i = 0; i < MAZE_SIZE; i++) {
		for (int j = 0; j < MAZE_SIZE; j++) {
			printf(" %c", maze[i][j]);
		}
		printf("\n");
	}
	printf("[ -------- 미로 --------- ] \n");
}

void main()
{
	int r, c, dir;
	int nextrow, nextcol, i;
	int flag = 0;
	int found = false;
	Object pos;
	stack* s = (stack*)malloc(sizeof(stack));

	init_stack(s); 
	pos = entry;
	maze[pos.r][pos.c] = '.';
	push(s, pos);

	while (s->top > -1 && !found) {
		pos = pop(s);
		r = pos.r;
		c = pos.c;
		dir = pos.dir;
		while (dir < 4 && !found) { //방향 잘..
			nextrow = r + move[dir].v;
			nextcol = c + move[dir].h;
			if (maze[nextrow][nextcol] == 'x') {
				found = true;
				pos.r = r; pos.c = c;
				pos.dir = ++dir;
				push(s, pos);
			}
			else if (maze[nextrow][nextcol] != '1' &&
				maze[nextrow][nextcol] != '.') { 
				maze[nextrow][nextcol] = '.';
				pos.r = r; pos.c = c;
				pos.dir = ++dir;
				push(s, pos);
				r = nextrow; c = nextcol; dir = 0; 
			}
			else
				++dir;
		} 
	} 

	maze_print(maze);

	if (found) { 
		printf("경로 : \n");
		printf("<row   col>\n");
		for (i = 0; i <= s->top; i++)
			printf("< %d   %d > \n", s->data[i].r, s->data[i].c);
		printf("< %d   %d > \n", EXIT_ROW, EXIT_COL);
	}
	else
		printf("경로없음\n");
}

#endif