#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ELEMENT {
	int id_num;
	char name[10];
}element;

typedef struct TreeNode {
	element std;
	struct TreeNode* left, * right;
} TreeNode;

TreeNode* create_node(element item)
{
	TreeNode* new_node = (TreeNode*)malloc(sizeof(TreeNode));

	if (new_node == NULL) {
		fprintf(stderr, "메모리 할당 에러\n");
		exit(1);
	}

	new_node->std = item;
	new_node->left = NULL;
	new_node->right = NULL;

	return new_node;
}

TreeNode* insert_node(TreeNode* root, element item)
{
	if (root == NULL) {
		root = create_node(item);
	}
	else if (item.id_num < root->std.id_num) {
		root->left = insert_node(root->left, item);
	}
	else if (item.id_num > root->std.id_num) {
		root->right = insert_node(root->right, item);
	}

	return root;
}

TreeNode* min_value_node(TreeNode* node)
{
	TreeNode* current = node;

	while (current->left != NULL) {
		current = current->left;
	}

	return current;
}

TreeNode* delete_node(TreeNode* root, int key)
{
	if (root == NULL) {
		return root;
	}

	if (key < root->std.id_num) {
		root->left = delete_node(root->left, key);
	}
	else if (key > root->std.id_num) {
		root->right = delete_node(root->right, key);
	}
	else {
		if (root->left == NULL) {
			TreeNode* tmp = root->right;
			free(root);
			return tmp;
		}
		else if (root->right == NULL) {
			TreeNode* tmp = root->left;
			free(root);
			return tmp;
		}

		TreeNode* tmp = min_value_node(root->right);
		root->std = tmp->std;
		root->right = delete_node(root->right, tmp->std.id_num);
	}

	return root;
}

TreeNode* search(TreeNode* root, int key)
{
	if (root == NULL || root->std.id_num == key) {
		return root;
	}

	if (key < root->std.id_num) {
		return search(root->left, key);
	}
	else {
		return search(root->right, key);
	}
}

TreeNode* delete_tree(TreeNode* root)
{
	if (root != NULL) {
		delete_tree(root->left);
		delete_tree(root->right);
		printf("[ %d ]\t", root->std.id_num);
		free(root);
	}

	return NULL;
}

int get_node_count(TreeNode* root)
{
	if (root == NULL) {
		return 0;
	}
	return 1 + get_node_count(root->left) + get_node_count(root->right);
}

int get_leaf_count(TreeNode* root) {
	if (root == NULL) {
		return 0;
	}
	if (root->left == NULL && root->right == NULL) {
		return 1;
	}
	return get_leaf_count(root->left) + get_leaf_count(root->right);
}

int get_height(TreeNode* root) {
	if (root == NULL) {
		return 0;
	}
	int left_height = get_height(root->left);
	int right_height = get_height(root->right);
	return 1 + (left_height > right_height ? left_height : right_height);
}

#define MAX_QUEUE_SIZE 100
typedef struct {
	TreeNode* node;
	int level;
}TreeNodeForLevelSearch;
typedef struct { // 큐 타입
	TreeNodeForLevelSearch  data[MAX_QUEUE_SIZE];
	int  front, rear;
} QueueNode;

// 오류 함수
void error(const char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

// 공백 상태 검출 함수
void init_queue(QueueNode* q)
{
	q->front = q->rear = 0;
}

// 공백 상태 검출 함수
int is_empty(QueueNode* q)
{
	return (q->front == q->rear);
}

// 포화 상태 검출 함수
int is_full(QueueNode* q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

// 삽입 함수
void en_queue(QueueNode* q, TreeNodeForLevelSearch node)
{
	if (is_full(q))
		error("큐가 포화상태입니다");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = node;
}

// 삭제 함수
TreeNodeForLevelSearch de_queue(QueueNode* q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}


// 중위 순회 함수
void inorder(TreeNode* root) {
	if (root != NULL) {
		inorder(root->left);
		printf("[ %d ]\t", root->std.id_num);
		inorder(root->right);
	}
}

// 레벨 탐색 순회 함수
void level_order(TreeNode* ptr)
{
	QueueNode q;
	TreeNodeForLevelSearch qdata, qdata2;
	int level;

	init_queue(&q);	 // 큐 초기화

	if (ptr == NULL) {
		printf("공백 트리입니다.\n");
		return ;
	}
	level = 0;
	qdata.level = 1;
	qdata.node = ptr;
	en_queue(&q, qdata);

	//printf("레벨순회 \n");
	while (!is_empty(&q)) {
		qdata = de_queue(&q);
		if (level != qdata.level) {
			printf("\n Level %d : ", qdata.level); level = qdata.level;
		}
		printf(" [%d] ", qdata.node->std.id_num);
		if (qdata.node->left) {
			qdata2.level = qdata.level + 1;
			qdata2.node = qdata.node->left;
			en_queue(&q, qdata2);
		}
		if (qdata.node->right) {
			qdata2.level = qdata.level + 1;
			qdata2.node = qdata.node->right;
			en_queue(&q, qdata2);
		}
	}
}

int main(void)
{
	TreeNode* root = NULL;
	TreeNode* tmp = NULL;
	element item;
	item.id_num = 2021006; 
	strcpy(item.name, "name6");
	root = insert_node(root, item);

	item.id_num = 2021001; 
	strcpy(item.name, "name1");
	root = insert_node(root, item);

	item.id_num = 2021009; 
	strcpy(item.name, "name9");
	root = insert_node(root, item);

	item.id_num = 2021007; 
	strcpy(item.name, "name7");
	root = insert_node(root, item);

	item.id_num = 2021003;
	strcpy(item.name, "name3");
	root = insert_node(root, item);

	item.id_num = 2021002; 
	strcpy(item.name, "name2");
	root = insert_node(root, item);

	item.id_num = 2021005;
	strcpy(item.name, "name5");
	root = insert_node(root, item);

	item.id_num = 2021004;
	strcpy(item.name, "name4");
	root = insert_node(root, item);

	item.id_num = 2021008; 
	strcpy(item.name, "name8");
	root = insert_node(root, item);

	item.id_num = 2021010;
	strcpy(item.name, "name10");
	root = insert_node(root, item);

	printf("이진 탐색 트리의 노드 수, leaf노드 수, 높이 구하기\n");
	printf("노드 수 = %d \nleaf 노드 수 = %d \n높이 = %d \n\n", get_node_count(root), get_leaf_count(root), get_height(root));
	printf("이진 탐색 트리 레벨 탐색 순회 결과\n");
	level_order(root);
	printf("\n\n");

	printf("이진 탐색 트리 중위 순회 결과 \n");
	inorder(root);
	printf("\n\n이진 탐색 트리에서 2021010 검색\n");
	tmp = search(root, 2021010);

	if (tmp != NULL)
		printf("검색 성공 : 학번 %d, 이름 %s \n", tmp->std.id_num,
			tmp->std.name);
	else
		printf("이진 탐색 트리에서 검색 학생을 발견못함 \n");

	printf("\n이진 탐색 트리에서 2021006 삭제\n");
	delete_node(root, 2021006);
	printf("\n\n이진 탐색 트리에서 2021006 검색\n");
	tmp = search(root, 2021006);

	if (tmp != NULL)
		printf("검색 성공 : 학번 %d, 이름 %s \n", tmp->std.id_num,
			tmp->std.name);
	else
		printf("이진 탐색 트리에서 검색 학생을 발견못함 \n");

	printf("\n\n이진 탐색 트리 중위 순회 결과 \n");
	inorder(root);
	printf("\n\n");

	printf("\n\n이진 탐색 트리 전체 삭제 \n");
	printf("노드 삭제 순서 :");
	root = delete_tree(root);

	printf("\n\n이진 탐색 트리 레벨 탐색 순회 결과\n");
	level_order(root);
	printf("\n\n");

	return 0;
}