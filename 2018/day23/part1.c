#include <stdio.h>
#include <stdlib.h>

#define LEN 1000

typedef struct _Bot {
	int x, y, z;
	int r;
} Bot;

int main() {
	int iMax = 0;
	Bot bots[LEN];

	for (int i = 0; i < LEN; ++i) {
		scanf("pos=<%d,%d,%d>, r=%d\n", &bots[i].x, &bots[i].y, &bots[i].z, &bots[i].r);
		if (bots[i].r > bots[iMax].r)
			iMax = i;
	}

	int result = 0;
	for (int i = 0; i < LEN; ++i) {
		if (abs(bots[i].x-bots[iMax].x) + abs(bots[i].y-bots[iMax].y) + abs(bots[i].z-bots[iMax].z) <= bots[iMax].r) {
			++result;
		}
	}
	printf("Result: %d\n", result);

	return 0;
}
