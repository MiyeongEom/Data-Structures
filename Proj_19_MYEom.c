#include <stdio.h>
#include <stdlib.h>

// 해싱 테이블의 내용을 출력
#define TABLE_SIZE 10000 // 가능하면 해싱 테이블의 크기를 소수로 설정 
typedef struct {
	int key;
} element;

struct list
{
	element item;
	struct list* link;
};

// 제산 함수를 사용한 해싱 함수
int hash_function(int key)
{
    return key % TABLE_SIZE;
}

#define SIZE TABLE_SIZE/5
#define SEARCH_COUNT 1000000

element* Lhash_table;
struct list** Chash_table;

// 선형 기법을 사용한 해시 테이블 초기화
void init_Lhash_table(element* ht, int size)
{
    for (int i = 0; i < size; i++)
        ht[i].key = 0;
}

// 체인 기법을 사용한 해시 테이블 초기화
void init_Chash_table(struct list** ht, int size)
{
    for (int i = 0; i < size; i++)
        ht[i] = NULL;
}

// 이중 해싱을 적용한 버킷 사이즈보다 작은 가장 큰 소수 구하기
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

// 선형 기법을 사용한 해시 테이블에 요소 추가
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

// 체인 기법을 사용한 해시 테이블에 요소 추가
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

// 선형 기법을 사용한 해시 테이블에서 요소 검색
void hash_linear_search(element e, element* ht, int h_prime)
{
    int key = e.key;
    int hash_value = hash_function(key);
    int i = 1;

    while (ht[hash_value].key != key) {
        hash_value = (hash_value + i) % TABLE_SIZE;
        i++;
        if (i == TABLE_SIZE) // 해시 테이블 전체를 검색한 경우
            break;
    }
}
// 체인 기법을 사용한 해시 테이블에서 요소 검색
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
// 해싱 테이블을 사용한 예제 
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
	h_prime = get_prime_number(TABLE_SIZE); //이중 해시법을 적용하기 위한 버킷 사이즈보다 작은 가장 큰 소수 구하기
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
	printf("선형기법\n");
	printf("적재율 %f 인경우 %d회 검색 시 소요 시간 %d \n", (float)SIZE / TABLE_SIZE, SEARCH_COUNT, e_time - s_time);
	srand(200);
	s_time = clock();
	for (int i = 0; i < SEARCH_COUNT; i++) {
		e.key = rand();
		hash_chain_search(e, Chash_table);
	}
	e_time = clock();
	printf("체인기법\n");
	printf("적재율 %f 인경우 %d회 검색 시 소요 시간 %d \n ", (float)SIZE /
		TABLE_SIZE, SEARCH_COUNT, e_time - s_time); 
	return 0;
}
