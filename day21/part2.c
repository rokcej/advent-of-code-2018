#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INSTS 31

#define FUNCS 16

typedef struct _Inst {
	void (*func)(int a, int b, int c);
	int a, b, c;
} Inst;

int reg[6] = { 0 };

void addr(int a, int b, int c) { reg[c] = reg[a] + reg[b]; }
void addi(int a, int b, int c) { reg[c] = reg[a] + b; }

void mulr(int a, int b, int c) { reg[c] = reg[a] * reg[b]; }
void muli(int a, int b, int c) { reg[c] = reg[a] * b; }

void banr(int a, int b, int c) { reg[c] = reg[a] & reg[b]; }
void bani(int a, int b, int c) { reg[c] = reg[a] & b; }

void borr(int a, int b, int c) { reg[c] = reg[a] | reg[b]; }
void bori(int a, int b, int c) { reg[c] = reg[a] | b; }

void setr(int a, int b, int c) { reg[c] = reg[a]; }
void seti(int a, int b, int c) { reg[c] = a; }

void gtir(int a, int b, int c) { reg[c] = (a > reg[b] ? 1 : 0); }
void gtri(int a, int b, int c) { reg[c] = (reg[a] > b ? 1 : 0); }
void gtrr(int a, int b, int c) { reg[c] = (reg[a] > reg[b] ? 1 : 0); }

void eqir(int a, int b, int c) { reg[c] = (a == reg[b] ? 1 : 0); }
void eqri(int a, int b, int c) { reg[c] = (reg[a] == b ? 1 : 0); }
void eqrr(int a, int b, int c) { reg[c] = (reg[a] == reg[b] ? 1 : 0); }

void print() {
	printf("[");
	for (int i = 0; i < 6; ++i) {
		printf("%d", reg[i]);
		if (i < 5)
			printf(", ");
	}
	printf("]\n");
	fflush(stdout);
}

int main() {
	// Read input
	int ip = 0;
	int ipReg;
	scanf("#ip %d\n", &ipReg);

	Inst insts[INSTS];
	for (int i = 0; i < INSTS; ++i) {
		char name[5];
		scanf("%s %d %d %d\n", name, &insts[i].a, &insts[i].b, &insts[i].c);

		void (*funcs[FUNCS])(int a, int b, int c) = {
			addr, addi, mulr, muli, banr, bani, borr, bori,
			setr, seti, gtir, gtri, gtrr, eqir, eqri, eqrr
		};
		char names[FUNCS][5] = {
			"addr", "addi", "mulr", "muli", "banr", "bani", "borr", "bori",
			"setr", "seti", "gtir", "gtri", "gtrr", "eqir", "eqri", "eqrr"
		};

		for (int j = 0; j < FUNCS; ++j) {
			if (strcmp(name, names[j]) == 0) {
				insts[i].func = funcs[j];
				break;
			}
		}
	}

	// Calculate result
	int set = 0;

	int lenMax = 256;
	int len = 0;
	int *cache = malloc(lenMax * sizeof(int));
	
	// Run until reg[3] repeats itself, result is the previous value
	while (ip >= 0 && ip < INSTS) {
		reg[ipReg] = ip;
		insts[ip].func(insts[ip].a, insts[ip].b, insts[ip].c);
		if (ip == 28) {
			if (set) {
				int found = 0;
				for (int i = 0; i < len; ++i) {
					if (reg[3] == cache[i]) {
						found = 1;
						break;
					}
				}
				if (found) {
					break;
				}
				if (len == lenMax) {
					lenMax <<= 1;
					cache = realloc(cache, lenMax * sizeof(int));
				}
				cache[len++] = reg[3];
			} else {
				cache[len++] = reg[3];
				set = 1;
			}
		}
		ip = reg[ipReg] + 1;
	}
	printf("Result: %d\n", cache[len-1]);

	return 0;
}
