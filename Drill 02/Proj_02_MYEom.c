#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>

int rec_count = 0; //재귀적 함수 호출 횟수를 저장하기 위한 함수
#define PROB 1 // 각각의 문제를 구현하고 해당 문제 번호를 변경하여 테스트

#if PROB == 1
/* Compute power(x, n) for int x, n */
// 1번 문제에 대한 반복, 재귀적 방법으로 구현하기 위한 각각의 함수 구현
// main 함수에서 데이터를 입력받아 호출하는 코드와 결과 출력 구현

double rec(int x, int n) {   //재귀
	rec_count += 1;
	if (n == 0)
		return 1;
	else if ((n % 2) == 0)
		return rec(x * x, n / 2);
	else return x * rec(x * x, (n - 1) / 2);
}

double itr(int x, int n) { //반복
	double result = 1.0;
	for (int i = 0; i < n; i++)
		result = result * x;
	return(result);
}

int main() {
	int x, n;
	double i, r;
	clock_t start, stop;
	double duration1, duration2;

	printf(" x, n 입력 <x^n> : ");
	scanf_s("%d %d", &x, &n);

	start = clock();
	i = itr(x, n);
	stop = clock();
	duration1 = (double)(stop - start) / CLOCKS_PER_SEC;

	start = clock();
	r = rec(x, n);
	stop = clock();
	duration2 = (double)(stop - start) / CLOCKS_PER_SEC;

	printf(" ITR : %d^%d = %lf, 수행시간 : %lf \n", x, n, i, duration1);
	printf(" REC : %d^%d = %lf, 수행시간 : %lf, 함수호출횟수 : %d \n", x, n, r, duration2, rec_count);
}



#elif PROB == 2
/* Binomial Coef */
// 2번 문제에 대한 반복, 재귀적 방법으로 구현하기 위한 각각의 함수 구현
// main 함수에서 데이터를 입력받아 호출하는 코드와 결과 출력 구현

int rec(int n, int k){   //재귀
	rec_count += 1;
	if (k == 0 || k == n)
		return 1;

	else
		return (rec(n - 1, k - 1) + rec(n - 1, k));  //이항 계산
}

int itr(int n, int k){ //반복
	int i, j;
	int a[100][100] = {};
	for (i = 1; i <= n; i++) {
		for (j = 0; j <= i; j++) {
			if (j == 0 || j == i) a[i][j] = 1;
			else a[i][j] = a[i - 1][j - 1] + a[i - 1][j];
}
	}
	return a[n][k];
}

int main(){
	int n, k, i, r;
	clock_t start, stop;
	double duration1, duration2;

	printf(" n, k 입력 <n >= k>) : ");
	scanf_s("%d %d", &n, &k);

	start = clock();
	i = itr(n, k);
	stop = clock();
	duration1 = (double)(stop - start) / CLOCKS_PER_SEC;

	start = clock();
	r = rec(n, k);
	stop = clock();
	duration2 = (double)(stop - start) / CLOCKS_PER_SEC;

	printf(" ITR : %dC%d = %d, 수행시간 : %lf \n", n, k, i, duration1);
	printf(" REC : %dC%d = %d, 수행시간 : %lf, 함수호출횟수 : %d \n", n, k, r, duration2, rec_count);
}



#elif PROB == 3
/* Ackerman function */
#define MAX_SIZE 1000000
int itr(int m, int n) {
	int* list = NULL;
	long long int esp = 0;

	list = (int*)malloc(sizeof(int) * MAX_SIZE);
	list[esp++] = m;
	list[esp] = n;

	while (1) {
		if (esp == 0) {
			return list[esp];
		}

		else if (list[esp - 1] == 0) {
			list[esp - 1] = list[esp] + 1;
			esp = esp - 1;
		}

		else if (list[esp] == 0) {
			list[esp - 1] = list[esp - 1] - 1;
			list[esp] = 1;
		}

		else {
			list[esp + 1] = list[esp] - 1;
			list[esp] = list[esp - 1];
			list[esp - 1] = list[esp - 1] - 1;

			esp = esp + 1;
		}
	}
}

int rec(int m, int n) {
	rec_count += 1;
	if (m == 0)
		return (n + 1);
	else if (n == 0)
		return rec(m - 1, 1);
	else
		return rec(m - 1, rec(m, n - 1));
}

int main() {
	int n, m, i, r;
	clock_t start, stop;
	double duration1, duration2;

	printf(" m, n 입력 <m, n >= 0>) : ");
	scanf_s("%d %d", &m, &n);

	start = clock();
	i = itr(m, n);
	stop = clock();
	duration1 = (double)(stop - start) / CLOCKS_PER_SEC;

	start = clock();
	r = rec(m, n);
	stop = clock();
	duration2 = (double)(stop - start) / CLOCKS_PER_SEC;
	
	printf(" ITR : A:<%d, %d> = %d, 수행시간 : %lf \n", m, n, i, duration1);
	printf(" REC : A:<%d, %d> = %d, 수행시간 : %lf, 함수호출횟수 : %d \n", m , n, r, duration2, rec_count);

	return 0;
}

#elif PROB == 4
/* 문제 3) 피보나치 수열 */
int rec(int n) {
	rec_count += 1;
	if (n == 0) 
		return 0;

	else if (n == 1) 
		return 1;

	return rec(n - 2) + rec(n - 1);
}

int itr(int n)
{
	int fib = 0, fib_one = 0, fib_two = 1;

	if (n == 0) 
		return 0;

	else if (n == 1) 
		return 1;

	else {
		for (int i = 2; i <= n; i++) {
			fib = fib_two + fib_one;
			fib_one = fib_two;
			fib_two = fib;
		}
	}
	return fib;
}

int main() {
	int m, i, r;
	clock_t start, stop;
	double duration1, duration2;

	printf("Input 피보나치 항 : ");
	scanf_s("%d", &m);

	start = clock();
	i = itr(m);
	stop = clock();
	duration1 = (double)(stop - start) / CLOCKS_PER_SEC;

	start = clock();
	r = rec(m);
	stop = clock();
	duration2 = (double)(stop - start) / CLOCKS_PER_SEC;

	printf(" ITR : 10 번째 항의 값 : %d, 수행시간 : %lf \n", i, duration1);
	printf(" REC : 10 번째 항의 값 : %d, 수행시간 : %lf, 함수호출횟수 : %d \n", r, duration2, rec_count);

	return 0;
}

#elif PROB == 5
/* 문제 4) Binary Search */

#define SIZE 100000

int rec(int a, int left, int right, int* data){	
	int middle = (left + right) / 2;
	rec_count += 1;
	if (left > right) 
		return -1;

	else if (a == data[middle])
		return middle;

	else {
		if (a > data[middle]) 
			return rec(a, middle + 1, right, data);
		else return rec(a, left, middle - 1, data);
	}
}

int itr(int a, int left, int right, int* data){
	int middle;

	while (left < right) {
		middle = (left + right) / 2;

		if (data[middle] == a) 
			return middle;

		else if (data[middle] > a) 
			right = middle - 1;

		else left = middle + 1;
	}

	return -1; // 찾지 못하였을 경우
}

int main() {
	clock_t start, stop;
	double duration1, duration2;

	int* data = (int*)malloc(sizeof(int) * SIZE);
	int index, i, r;
	int a = 5000;

	if (data == NULL)
		printf("Data 오류");

	for (index = 0; index < SIZE; index++)
		data[index] = index;

	start = clock();
	i = itr(a, 0, SIZE - 1, data);
	stop = clock();
	duration1 = (double)(stop - start) / CLOCKS_PER_SEC;

	start = clock();
	r = rec(a, 0, SIZE - 1, data);
	stop = clock();
	duration2 = (double)(stop - start) / CLOCKS_PER_SEC;

	printf(" ITR : %d 값의 index : %d, 수행시간 : %lf \n", a, i, duration1);
	printf(" REC : %d 값의 index : %d, 수행시간 : %lf, 함수호출횟수 : %d \n", a, r, duration2, rec_count);

	return 0;
}
#endif