#include <stdio.h>
#include <stdlib.h>

// �ؽ� ���̺��� ������ ���
#define TABLE_SIZE 10000 // �����ϸ� �ؽ� ���̺��� ũ�⸦ �Ҽ��� ���� 
typedef struct {
	int key;
} element;

struct list
{
	element item;
	struct list* link;
};

// ���� �Լ��� ����� �ؽ� �Լ�
int hash_function(int key)
{
    return key % TABLE_SIZE;
}

#define SIZE TABLE_SIZE/5
#define SEARCH_COUNT 1000000

element* Lhash_table;
struct list** Chash_table;

// ���� ����� ����� �ؽ� ���̺� �ʱ�ȭ
void init_Lhash_table(element* ht, int size)
{
    for (int i = 0; i < size; i++)
        ht[i].key = 0;
}

// ü�� ����� ����� �ؽ� ���̺� �ʱ�ȭ
void init_Chash_table(struct list** ht, int size)
{
    for (int i = 0; i < size; i++)
        ht[i] = NULL;
}

// ���� �ؽ��� ������ ��Ŷ ������� ���� ���� ū �Ҽ� ���ϱ�
int get_prime_number(int size)
{
    int n = size - 1;
    int prime = 0;

    while (1) {
        n++;
        int i;
        for (i = 2; i < n; i++) {
            if (n % i == 0)
                break;
        }
        if (i == n) {
            prime = n;
            break;
        }
    }
    return prime;
}

// ���� ����� ����� �ؽ� ���̺� ��� �߰�
void hash_linear_add(element e, element* ht, int h_prime)
{
    int key = e.key;
    int hash_value = hash_function(key);
    int i = 1;

    while (ht[hash_value].key != 0) {
        hash_value = (hash_value + i) % TABLE_SIZE;
        i++;
    }
    ht[hash_value] = e;
}

// ü�� ����� ����� �ؽ� ���̺� ��� �߰�
void hash_chain_add(element e, struct list** ht)
{
    int key = e.key;
    int hash_value = hash_function(key);

    struct list* node = (struct list*)malloc(sizeof(struct list));
    node->item = e;
    node->link = NULL;

    if (ht[hash_value] == NULL) {
        ht[hash_value] = node;
    }
    else {
        struct list* temp = ht[hash_value];
        while (temp->link != NULL)
            temp = temp->link;
        temp->link = node;
    }
}

// ���� ����� ����� �ؽ� ���̺��� ��� �˻�
void hash_linear_search(element e, element* ht, int h_prime)
{
    int key = e.key;
    int hash_value = hash_function(key);
    int i = 1;

    while (ht[hash_value].key != key) {
        hash_value = (hash_value + i) % TABLE_SIZE;
        i++;
        if (i == TABLE_SIZE) // �ؽ� ���̺� ��ü�� �˻��� ���
            break;
    }
}
// ü�� ����� ����� �ؽ� ���̺��� ��� �˻�
void hash_chain_search(element e, struct list** ht)
{
    int key = e.key;
    int hash_value = hash_function(key);

    struct list* temp = ht[hash_value];

    while (temp != NULL) {
        if (temp->item.key == key)
            break;
        temp = temp->link;
    }
}
// �ؽ� ���̺��� ����� ���� 
int main(void)
{
	int s_time, e_time;
	int h_prime;
	element e;
	Lhash_table = (element*)malloc(sizeof(element) * TABLE_SIZE);
	Chash_table = (struct list**)malloc(sizeof(struct list*) * TABLE_SIZE);
	init_Lhash_table(Lhash_table, TABLE_SIZE);
	init_Chash_table(Chash_table, TABLE_SIZE);
	srand(100);
	h_prime = get_prime_number(TABLE_SIZE); //���� �ؽù��� �����ϱ� ���� ��Ŷ ������� ���� ���� ū �Ҽ� ���ϱ�
		for (int i = 0; i < SIZE; i++) {
			e.key = rand();
			hash_linear_add(e, Lhash_table, h_prime);
			hash_chain_add(e, Chash_table);
		}
	srand(200);
	s_time = clock();
	for (int i = 0; i < SEARCH_COUNT; i++) {
		e.key = rand();
		hash_linear_search(e, Lhash_table, h_prime);
	}
	e_time = clock();
	printf("�������\n");
	printf("������ %f �ΰ�� %dȸ �˻� �� �ҿ� �ð� %d \n", (float)SIZE / TABLE_SIZE, SEARCH_COUNT, e_time - s_time);
	srand(200);
	s_time = clock();
	for (int i = 0; i < SEARCH_COUNT; i++) {
		e.key = rand();
		hash_chain_search(e, Chash_table);
	}
	e_time = clock();
	printf("ü�α��\n");
	printf("������ %f �ΰ�� %dȸ �˻� �� �ҿ� �ð� %d \n ", (float)SIZE /
		TABLE_SIZE, SEARCH_COUNT, e_time - s_time); 
	return 0;
}
