#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef struct TreeNode {
	int data;
	struct TreeNode* left, * right;
} TreeNode;

TreeNode n15 = { 15,  NULL, NULL };
TreeNode n14 = { 14,  NULL, NULL };
TreeNode n13 = { 13,  NULL, NULL };
TreeNode n12 = { 12,  NULL,  NULL };
TreeNode n11 = { 11, NULL, NULL };
TreeNode n10 = { 10, NULL, NULL };
TreeNode n9 = { 9, NULL,  NULL };
TreeNode n8 = { 8, NULL,  NULL };
TreeNode n7 = { 7, &n14, &n15 };
TreeNode n6 = { 6, &n12, &n13 };
TreeNode n5 = { 5, &n10, &n11 };
TreeNode n4 = { 4, &n8, &n9 };
TreeNode n3 = { 3, &n6, &n7 };
TreeNode n2 = { 2, &n4, &n5 };
TreeNode n1 = { 1, &n2, &n3 };
TreeNode* root = &n1;

typedef struct NODE { int data; int leaf; } node;
node arr[] = { {0,0}, {1,1}, {2,1}, {3,1}, {4,1}, {5,1}, {6,1}, {7,1}, {8,0}, {9,0}, {10,0}, {11,0},
{12,0}, {13,0}, {14,0}, {15,0} };

void inorder_rec(TreeNode* root) {
	if (root != NULL) {
		inorder_rec(root->left);
		printf("[%d] ", root->data);  
		inorder_rec(root->right);
	}
}

void preorder_rec(TreeNode* root) {
	if (root != NULL) {
		printf("[%d] ", root->data);  
		preorder_rec(root->left);
		preorder_rec(root->right);
	}
}

void postorder_rec(TreeNode* root) {
	if (root != NULL) {
		postorder_rec(root->left);
		postorder_rec(root->right);
		printf("[%d] ", root->data); 
	}
}

#define STACK_SIZE 100
typedef struct STACK {
	TreeNode* data[STACK_SIZE];
	int top;
}STACK;

void init_stack(STACK* s)
{
	s->top = -1;
}

void push(STACK* s, TreeNode* p)
{
	if (s->top < STACK_SIZE - 1)
		s->data[++(s->top)] = p;
}

TreeNode* pop(STACK* s)
{
	TreeNode* p = NULL;
	if (s->top >= 0)
		p = s->data[s->top--];
	return p;
}

int is_empty(STACK* s)
{
	if (s->top == -1) return 1; else return 0;
}

void inorder_iter(TreeNode* root)
{
	STACK s;
	init_stack(&s);

	while (1) {
		for (; root; root = root->left)
			push(&s, root);
		root = pop(&s);
		if (!root) break;
		printf("[%d] ", root->data);
		root = root->right;
	}
}

void preorder_iter(TreeNode* root)
{
	TreeNode* node;
	STACK s;
	init_stack(&s);

	if (!root) return;
	push(&s, root);

	while (!is_empty(&s)) {
		node = pop(&s);
		printf("[%d] ", node->data);
		if (node->right != NULL) push(&s, node->right);
		if (node->left != NULL) push(&s, node->left); //왼쪽이 먼저 pop되게
	}
}

void postorder_iter(TreeNode* root)
{
	TreeNode* node;
	STACK s1, s2;

	init_stack(&s1);
	push(&s1, root);

	init_stack(&s2);

	while (!is_empty(&s1))
	{
		node = pop(&s1);
		push(&s2, node);

		if (node->left) {
			push(&s1, node->left);
		}
		if (node->right) {
			push(&s1, node->right);
		}
	}

	while (!is_empty(&s2)) {
		printf("[%d] ", pop(&s2)->data);
	}
}

void inorder_rec_arr(node* arr, int index) {
	if (index >= 16) {
		return;
	}
	inorder_rec_arr(arr, 2 * index);
	printf("[%d] ", arr[index].data);
	inorder_rec_arr(arr, 2 * index + 1);
}

void preorder_rec_arr(node* arr, int index) {
	if (index >= 16) {
		return;
	}
	printf("[%d] ", arr[index].data);
	preorder_rec_arr(arr, 2 * index);
	preorder_rec_arr(arr, 2 * index + 1);
}

void postorder_rec_arr(node* arr, int index) {
	if (index >= 16) {
		return;
	}
	postorder_rec_arr(arr, 2 * index);
	postorder_rec_arr(arr, 2 * index + 1);
	printf("[%d] ", arr[index].data);
}

int main(void)
{
	int size = sizeof(arr) / sizeof(arr[0]);
	printf("중위 순회(rec) =");
	inorder_rec(root);
	printf("\n");
	printf("중위 순회(itr) =");
	inorder_iter(root);
	printf("\n");
	printf("배열 중위 순회(rec)=");
	inorder_rec_arr(arr, 1);
	printf("\n\n");
	printf("전위 순회(rec) =");
	preorder_rec(root);
	printf("\n");
	printf("전위 순회(itr) =");
	preorder_iter(root);
	printf("\n");
	printf("배열 전위 순회(rec)=");
	preorder_rec_arr(arr, 1);
	printf("\n\n");
	printf("후위 순회(rec) =");
	postorder_rec(root);
	printf("\n");
	printf("후위 순회(itr) =");
	postorder_iter(root);
	printf("\n");
	printf("배열 후위 순회(rec)=");
	postorder_rec_arr(arr, 1);
	printf("\n\n");
	return 0;
}