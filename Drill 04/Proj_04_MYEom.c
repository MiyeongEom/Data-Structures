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

// ���� �ʱ�ȭ �Լ�
void init_stack(StackType* s)
{
	s->top = -1;
}

// ���� ���� ���� �Լ�
int is_empty(StackType* s)
{
	return (s->top == -1);
}

// ��ȭ ���� ���� �Լ�
int is_full(StackType* s)
{
	return (s->top == (MAX_STACK_SIZE - 1));
}

// �����Լ�
void push(StackType* s, element item)
{
	if (is_full(s)) {
		fprintf(stderr, "���� ��ȭ ����\n");
		return;
	}
	else s->data[++(s->top)] = item;
}

// �����Լ�
element pop(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}
	else return s->data[(s->top)--];
}

// ��ũ�Լ�
element peek(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����\n");
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
	int i, n = strlen(in);  	// n= ���ڿ��� ����
	init_stack(&s);			// ������ �ʱ�ȭ

	for (i = 0; i < n; i++) {
		ch = in[i];		// ch = ���� ����
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
		printf("%s  : ��ȣ�˻缺��\n", p);
	else if (pos.second_pos == -1) {
		printf("%s  : ��ȣ�˻���� %d ��ġ \n", p, pos.first_pos);
		printf("01234567890123456789012345678901234567890123456789012345678901234567890123456789\n");
	}
	else {
		printf("%s ��ȣ�˻���� %d, %d ��ġ \n", p, pos.first_pos, pos.second_pos);
		printf("01234567890123456789012345678901234567890123456789012345678901234567890123456789\n");
	}

	return 0;
}