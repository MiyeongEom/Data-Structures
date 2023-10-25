#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PROB 2 // 각각의 문제를 구현하고 해당 문제 번호를 변경하여 테스트
#if PROB == 1
// 1번 문제를 해결하기 위한 프로그램 작성

#define SIZE 1000000 // 저장된 데이터의갯수
#define DATA 586321 // 찾는 키 값

int seqsearch(int* list, int start, int end, int target, int* count)
{
	*count = 0; 
	for (int i = start; i <= end; i++) {
		(*count)++;
		if (list[i] == target)
			return i;
	}
	return -1;
}

int binsearch(int* list, int start, int end, int target, int* count)
{
	*count = 0; 
	while (start <= end) {
		(*count)++;
		int mid = (start + end) / 2;
		if (list[mid] == target)
			return mid;
		else if (list[mid] < target)
			start = mid + 1;
		else
			end = mid - 1;
	}
	return -1;
}

int search_interpolation(int* list, int start, int end, int target, int* count)
{
	*count = 0; 
	while (start <= end && target >= list[start] && target <= list[end]) {
		(*count)++;
		if (start == end) {
			if (list[start] == target)
				return start;
			return -1;
		}

		int pos = start + (((double)(end - start) / (list[end] - list[start])) * (target - list[start]));

		if (list[pos] == target)
			return pos;

		if (list[pos] < target)
			start = pos + 1;
		else
			end = pos - 1;
	}
	return -1;
}

int main(void)
{
	int i, s_time, e_time, count, result;
	int* list = (int*)malloc(sizeof(int) * SIZE);
	if (list == NULL) { printf("메모리 할당 오류 \n"); exit(-1); }
	// 오름차순으로 정수 데이터 생성 및 저장
	list[0] = 0;
	for (i = 1; i < SIZE; i++)
		list[i] = list[i - 1] + (rand() % 3);
	printf("Data 크기 : %d, 검색 데이터 : %d \n", SIZE, DATA);
	printf("----------------------------------------------\n");
	s_time = clock();
	result = seqsearch(list, 0, SIZE - 1, DATA, &count); //순차탐색 호출
	e_time = clock();
	
	if (result == -1) 
		printf("검색 결과 : 검색 데이터 없음 \n");
	else 
		printf("검색결과 : %d 위치에서 찾음 \n", result);
	
	printf("순차탐색 소요시간 %d, 비교횟수 : %d\n\n", e_time - s_time, count);
	
	s_time = clock();
	result = binsearch(list, 0, SIZE - 1, DATA, &count); //이진탐색 호출
	e_time = clock();
	
	if (result == -1) 
		printf("검색 결과 : 검색 데이터 없음 \n");
	else 
		printf("검색결과 : %d 위치에서 찾음 \n", result);
	printf("이진탐색 소요시간 %d, 비교횟수 : %d\n\n", e_time - s_time, count);
	
	s_time = clock();
	result = search_interpolation(list, 0, SIZE - 1, DATA, &count);//보간탐색 호출
	e_time = clock();
	
	if (result == -1) 
		printf("검색 결과 : 검색 데이터 없음 \n");
	else
		printf("검색결과 : %d 위치에서 찾음 \n", result);
	
	printf("보간탐색 소요시간 %d, 비교횟수 : %d\n\n", e_time - s_time, count);
	free(list);
	return 0;
}



#elif PROB == 2
// 2번 문제를 해결하기 위한 프로그램 작성

typedef struct AVLNode
{
	int key;
	struct AVLNode* left;
	struct AVLNode* right;
} AVLNode;

AVLNode* new_node(int key)
{
	AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode));
	node->key = key;
	node->left = NULL;
	node->right = NULL;
	return node;
}

AVLNode* right_rotate(AVLNode* y)
{
	AVLNode* x = y->left;
	AVLNode* T2 = x->right;

	x->right = y;
	y->left = T2;

	return x;
}

AVLNode* left_rotate(AVLNode* x)
{
	AVLNode* y = x->right;
	AVLNode* T2 = y->left;

	y->left = x;
	x->right = T2;

	return y;
}

int get_balance(AVLNode* node)
{
	if (node == NULL)
		return 0;

	int left_height = get_height(node->left);
	int right_height = get_height(node->right);
	return left_height - right_height;
}

int get_height(AVLNode* node)
{
	if (node == NULL)
		return 0;

	int left_height = get_height(node->left);
	int right_height = get_height(node->right);
	return 1 + ((left_height > right_height) ? left_height : right_height);
}

AVLNode* AVL_insert(AVLNode* node, int key)
{
	if (node == NULL)
		return new_node(key);

	if (key < node->key)
		node->left = AVL_insert(node->left, key);
	else if (key > node->key)
		node->right = AVL_insert(node->right, key);
	else
		return node;

	int balance = get_balance(node);

	if (balance > 1 && key < node->left->key)
		return right_rotate(node);

	if (balance < -1 && key > node->right->key)
		return left_rotate(node);

	if (balance > 1 && key > node->left->key)
	{
		node->left = left_rotate(node->left);
		return right_rotate(node);
	}

	if (balance < -1 && key < node->right->key)
	{
		node->right = right_rotate(node->right);
		return left_rotate(node);
	}

	return node;
}

AVLNode* find_min(AVLNode* node)
{
	AVLNode* current = node;
	while (current->left != NULL)
		current = current->left;
	return current;
}

AVLNode* AVL_remove(AVLNode* root, int key)
{
	if (root == NULL)
		return root;

	if (key < root->key)
		root->left = AVL_remove(root->left, key);
	else if (key > root->key)
		root->right = AVL_remove(root->right, key);
	else
	{
		if (root->left == NULL || root->right == NULL)
		{
			AVLNode* temp = root->left ? root->left : root->right;
			if (temp == NULL)
			{
				temp = root;
				root = NULL;
			}
			else
				*root = *temp;
			free(temp);
		}
		else
		{
			AVLNode* temp = find_min(root->right);
			root->key = temp->key;
			root->right = AVL_remove(root->right, temp->key);
		}
	}

	if (root == NULL)
		return root;

	int balance = get_balance(root);

	if (balance > 1 && get_balance(root->left) >= 0)
		return right_rotate(root);

	if (balance > 1 && get_balance(root->left) < 0)
	{
		root->left = left_rotate(root->left);
		return right_rotate(root);
	}

	if (balance < -1 && get_balance(root->right) <= 0)
		return left_rotate(root);

	if (balance < -1 && get_balance(root->right) > 0)
	{
		root->right = right_rotate(root->right);
		return left_rotate(root);
	}

	return root;
}

void level_order(AVLNode* root)
{
	if (root == NULL)
		return;

	AVLNode** queue = (AVLNode**)malloc(sizeof(AVLNode*) * 100);
	int front = 0;
	int rear = 0;

	queue[rear++] = root;
	int current_level_count = 1;
	int next_level_count = 0;
	printf("Level Print\n");

	while (front < rear)
	{
		AVLNode* node = queue[front++];
;		printf("[%d],  ", node->key);
		current_level_count--;

		if (node->left != NULL)
		{
			queue[rear++] = node->left;
			next_level_count++;
		}

		if (node->right != NULL)
		{
			queue[rear++] = node->right;
			next_level_count++;
		}

		if (current_level_count == 0)
		{
			printf("\n");
			current_level_count = next_level_count;
			next_level_count = 0;
		}
	}

	free(queue);
	printf("---------------\n");
}

// 테스트를 위한 main 함수
int main(void)
{
	AVLNode* root = NULL;
	// 60 50 20 80 90 70 55 10 40 35
	
	// 예제 트리 구축
	printf("Insert %d\n", 60); root = AVL_insert(root, 60);
	printf("Insert %d\n", 50); root = AVL_insert(root, 50);
	printf("Insert %d\n", 20); root = AVL_insert(root, 20);
	level_order(root);
	printf("Insert %d\n", 80); root = AVL_insert(root, 80);
	level_order(root);
	printf("Insert %d\n", 90); root = AVL_insert(root, 90);
	level_order(root);
	printf("Insert %d\n", 70); root = AVL_insert(root, 70);
	level_order(root);
	printf("Insert %d\n", 55); root = AVL_insert(root, 55);
	level_order(root);
	printf("Insert %d\n", 10); root = AVL_insert(root, 10);
	level_order(root);
	printf("Insert %d\n", 40); root = AVL_insert(root, 40);
	level_order(root);
	printf("Insert %d\n", 35); root = AVL_insert(root, 35);
	level_order(root);
	printf("Remove %d\n", 50); root = AVL_remove(root, 50);
	level_order(root);
	printf("Remove %d\n", 55); root = AVL_remove(root, 55);
	level_order(root);
	return 0;
}

#endif