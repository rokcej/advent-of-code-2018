#include <stdio.h>

#define LEN 815
#define FUNC 16

int reg[4] = { 0 };

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

void (*func[FUNC])(int a, int b, int c) = {
	addr, addi, mulr, muli, banr, bani, borr, bori,
	setr, seti, gtir, gtri, gtrr, eqir, eqri, eqrr
};

void copy(int before[4]) {
	for (int i = 0; i < 4; ++i) {
		reg[i] = before[i];
	}
}

int equals(int after[4]) {
	for (int i = 0; i < 4; ++i) {
		if (reg[i] != after[i]) return 0;
	}
	return 1;
}

int main() {
	int count = 0;
	for (int i = 0; i < LEN; ++i) {
		int before[4], after[4];
		int op, a, b, c;
		scanf("Before: [%d, %d, %d, %d]\n", before, before+1, before+2, before+3);
		scanf("%d %d %d %d\n", &op, &a, &b, &c);
		scanf("After: [%d, %d, %d, %d]\n\n", after, after+1, after+2, after+3);

		int correct = 0;
		for (int f = 0; f < FUNC; ++f) {
			copy(before);
			func[f](a, b, c);
			if (equals(after)) {
				if (++correct >= 3) {
					++count;
					break;
				}
			}
		}
	}
	printf("Result: %d\n", count);
	return 0;
}
