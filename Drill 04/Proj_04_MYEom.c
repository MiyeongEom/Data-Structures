#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
typedef struct {
	char parenthesis;
	int  pos;
}element;
#define MAX_STACK_SIZE 100

typedef struct {
	int first_pos;
	int second_pos;
}fail_pos;

typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
} StackType;

// 스택 초기화 함수
void init_stack(StackType* s)
{
	s->top = -1;
}

// 공백 상태 검출 함수
int is_empty(StackType* s)
{
	return (s->top == -1);
}

// 포화 상태 검출 함수
int is_full(StackType* s)
{
	return (s->top == (MAX_STACK_SIZE - 1));
}

// 삽입함수
void push(StackType* s, element item)
{
	if (is_full(s)) {
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else s->data[++(s->top)] = item;
}

// 삭제함수
element pop(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->data[(s->top)--];
}

// 피크함수
element peek(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->data[s->top];
}

fail_pos check_matching(const char* in)
{
	StackType s;
	fail_pos f_pos = { -1, -1 };
	element item;

	char ch;
	int i, n = strlen(in);  	// n= 문자열의 길이
	init_stack(&s);			// 스택의 초기화

	for (i = 0; i < n; i++) {
		ch = in[i];		// ch = 다음 문자
		switch (ch) {
		case '(':   case '[':    case '{':
			item.parenthesis = ch; item.pos = i;
			push(&s, item);
			break;
		case ')':   case ']':    case '}':
			if (is_empty(&s)) {
				f_pos.first_pos = i; return f_pos;
			}
			else {
				item = pop(&s);
				if ((item.parenthesis == '(' && ch != ')') ||
					(item.parenthesis == '[' && ch != ']') ||
					(item.parenthesis == '{' && ch != '}')) {
					f_pos.first_pos = item.pos; f_pos.second_pos = i; return f_pos;
				}
				break;
			}
		}
	}
	if (!is_empty(&s)) { f_pos.first_pos = pop(&s).pos; return f_pos; } 
	return f_pos;
}

int main(void)
{
	fail_pos pos;
	const char* p = "A(x) = 24.5 * <x + func<x, y>> * <r * r * 3.14> / [7 % 10 * sqrt(25)]";

	pos = check_matching(p);
	if (pos.first_pos == -1 && pos.second_pos == -1)
		printf("%s  : 괄호검사성공\n", p);
	else if (pos.second_pos == -1) {
		printf("%s  : 괄호검사실패 %d 위치 \n", p, pos.first_pos);
		printf("01234567890123456789012345678901234567890123456789012345678901234567890123456789\n");
	}
	else {
		printf("%s 괄호검사실패 %d, %d 위치 \n", p, pos.first_pos, pos.second_pos);
		printf("01234567890123456789012345678901234567890123456789012345678901234567890123456789\n");
	}

	return 0;
}