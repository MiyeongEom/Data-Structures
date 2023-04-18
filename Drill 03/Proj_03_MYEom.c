#include <stdio.h>

#define PROB 1

#if PROB == 1

#define MAX(a,b)  (((a) > (b)) ? (a) : (b))
#define MAX_TERM 101 //최대 차수 100

typedef struct polynomial {
	int degree;
	int coef[MAX_TERM];
}POLY;

POLY addPoly(POLY A, POLY B) {
	POLY C;
	int Apos = 0, Bpos = 0, Cpos = 0;
	int degree_a = A.degree;
	int degree_b = B.degree;
	C.degree = MAX(A.degree, B.degree);
	while (Apos <= A.degree && Bpos <= B.degree) {
		if (degree_a > degree_b) {
			C.coef[Cpos++] = A.coef[Apos++];
			degree_a--;
		}
		else if (degree_a == degree_b) {
			C.coef[Cpos++] = A.coef[Apos++] + B.coef[Bpos++];
			degree_a--;
			degree_b--;
		}
		else {
			C.coef[Cpos++] = B.coef[Bpos++];
			degree_b--;
		}
	}
	return C;
}

POLY mulPoly(POLY A, POLY B) {
	POLY C;

	for (int i = 0; i < A.degree + B.degree + 1; i++) C.coef[i] = 0;
	C.degree = A.degree + B.degree;

	for (int i = 0; i < A.degree + 1; i++)
		for (int j = 0; j < B.degree + 1; j++)
			C.coef[i + j] += A.coef[i] * B.coef[j];

	return C;
}

void printPoly(char x[], POLY p) {
	printf("%s :", x);
	for (int i = p.degree; i > 0; i--) {
		printf("(%3.1ix^%d) +", p.coef[p.degree - i], i);
	}
	printf("(%3.1ix^0)\n", p.coef[p.degree]);
}

int main(void) {
	POLY a = { 5, {3, 0, 4, -2, 1, 7} }; // a(x) = 3x5 + 4x3 - 2x2 + 1x + 7
	POLY b = { 3, {4, 2, -6, -3} }; // b(x) = 4x3 + 2x2 - 6x - 3
	POLY c, d; //for result

	printPoly("a(x)", a);
	printPoly("b(x)", b);

	c = addPoly(a, b);
	printPoly("c(x) = a(x) + b(x) ", c);

	d = mulPoly(a, b);
	printPoly("d(x) = a(x) x b(x) ", d);
	
	return 0;
}


#elif PROB == 2

#define MAX_TERM 101 //최대 항의 수 100

typedef struct term { int coef; int exp; } TERM;
typedef struct polynomial {
	int num_of_terms;
	TERM terms[MAX_TERM];
}POLY;

void printPoly(char x[], POLY p) {
	printf("%s :", x);
	for (int i = 0; i < p.num_of_terms - 1; i++) {
		printf(" (%3.1ix^%d) +", p.terms[i].coef, p.terms[i].exp);
	}
	printf(" (%3.1ix^%d)\n", p.terms[p.num_of_terms - 1].coef, p.terms[p.num_of_terms - 1].exp);
}

int main(void) {
	POLY a = { 5, {3,5, 4,3, -2,2, 1,1, 7,0} }; // a(x) = 3x5 + 4x3 - 2x2 + 1x + 7
	POLY b = { 4, {4,3, 2,2, -6,1, -3,0} }; // b(x) = 4x3 + 2x2 - 6x - 3
	POLY c, d; //for result

	printPoly("a(x)", a);
	printPoly("b(x)", b);
	
	//c = addPoly(a, b);
	//printPoly("c(x) = a(x) + b(x) ", c);
	
	//d = mulPoly(a, b);
	//printPoly("d(x) = a(x) x b(x) ", d);
	
	return 0;
}

#endif