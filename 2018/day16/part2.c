#include <stdio.h>

#define SAMPLE_LEN 815
#define PROG_LEN 947
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
	// Read input
	void (*op[FUNC])(int a, int b, int c) = { NULL };
	void (*candidates[FUNC][FUNC])(int a, int b, int c) = { NULL };

	for (int i = 0; i < SAMPLE_LEN; ++i) {
		int before[4], after[4];
		int opcode, a, b, c;
		scanf("Before: [%d, %d, %d, %d]\n", before, before+1, before+2, before+3);
		scanf("%d %d %d %d\n", &opcode, &a, &b, &c);
		scanf("After: [%d, %d, %d, %d]\n\n", after, after+1, after+2, after+3);

		int j = 0;
		void (*correct[FUNC])(int a, int b, int c) = { NULL };

		for (int f = 0; f < FUNC; ++f) {
			copy(before);
			func[f](a, b, c);
			if (equals(after))
				correct[j++] = func[f];
		}

		if (candidates[opcode][0] == NULL) {
			for (int k = 0; k < j; ++k)
				candidates[opcode][k] = correct[k];
		} else {
			int k;
			for (k = 0; k < FUNC; ++k) {
				if (candidates[opcode][k] == NULL)
					break;
				int included = 0;
				for (int m = 0; m < j; ++m) {
					if (candidates[opcode][k] == correct[m]) {
						included = 1;
						break;
					}
				}
				if (!included) {
					candidates[opcode][k] = NULL;
				}
			}
			for (int m = 1; m < k; ++m) {
				int n = m;
				while (n > 0 && candidates[opcode][n-1] == NULL) {
					candidates[opcode][n-1] = candidates[opcode][n];
					candidates[opcode][n] = NULL;
					--n;
				}
			}
		}
	}
	// Remove already determined ops
	int removed[FUNC] = { 0 };
	for (int i = 0; i < FUNC;) {
		if (!removed[i] && candidates[i][1] == NULL) {
			for (int j = 0; j < FUNC; ++j) {
				if (j == i)
					continue;
				int k;
				for (k = 0; k < FUNC; ++k) {
					if (candidates[j][k] == NULL)
						break;
					if (candidates[j][k] == candidates[i][0])
						candidates[j][k] = NULL;
				}
				for (int m = 1; m < k; ++m) {
					int n = m;
					while (n > 0 && candidates[j][n-1] == NULL) {
						candidates[j][n-1] = candidates[j][n];
						candidates[j][n] = NULL;
						--n;
					}
				}
			}
			removed[i] = 1;
			i = 0;
			continue;
		}
		++i;
	}
	
	for (int i = 0; i < FUNC; ++i) {
		op[i] = candidates[i][0];
	}

	for (int i = 0; i < 4; ++i)
		reg[i] = 0;
	// Simulate program
	int opcode, a, b, c;
	while (scanf("%d %d %d %d\n", &opcode, &a, &b, &c) == 4)
		op[opcode](a, b, c);

	printf("Result: %d\n", reg[0]);
	return 0;
}
