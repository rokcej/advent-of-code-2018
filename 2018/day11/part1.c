#include <stdio.h>
#include <string.h>

#define FSIZE 300
#define SSIZE 3

int main() {
	int serial;
	scanf("%d", &serial);

	int totalSize = FSIZE - SSIZE + 1;
	int total[totalSize][totalSize];
	memset(&(total[0][0]), 0, totalSize * totalSize * sizeof(int));

	for (int i = 0; i < FSIZE; ++i) {
		for (int j = 0; j < FSIZE; ++j) {
			int x = j + 1;
			int y = i + 1;

			int rack = x + 10;
			int power = ((rack * y + serial) * rack) / 100 % 10 - 5;

			for (int it = (i-SSIZE+1 < 0 ? 0 : i-SSIZE+1); it <= i && it < totalSize; ++it) {
				for (int jt = (j-SSIZE+1 < 0 ? 0 : j-SSIZE+1); jt <= j && jt < totalSize; ++jt) {
					total[it][jt] += power;
				}
			}
		}
	}

	int resultX = 0;
	int resultY = 0;
	for (int i = 0; i < totalSize; ++i) {
		for (int j = 0; j < totalSize; ++j) {
			if (total[i][j] > total[resultY][resultX]) {
				resultX = j;
				resultY = i;
			}
		}
	}
	resultX += 1;
	resultY += 1;

	printf("Result: %d,%d\n", resultX, resultY);

	return 0;
}
