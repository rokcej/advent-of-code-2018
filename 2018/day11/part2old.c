// Old version of part 2

#include <stdio.h>
#include <string.h>

#define FSIZE 300

int main() {
	int serial;
	scanf("%d", &serial);

	int fuel[FSIZE][FSIZE];
	for (int i = 0; i < FSIZE; ++i) {
		for (int j = 0; j < FSIZE; ++j) {
			int x = j + 1;
			int y = i + 1;

			int rack = x + 10;
			int power = ((rack * y + serial) * rack) / 100 % 10 - 5;
			fuel[i][j] = power;
		}
	}

	int resultX = 0;
	int resultY = 0;
	int resultSize = 1;
	int max = fuel[0][0];

	int total[FSIZE][FSIZE];
	memset(&(total[0][0]), 0, FSIZE * FSIZE * sizeof(int));
	for (int size = 1; size <= FSIZE; ++size) {
		int totalSize = FSIZE - size + 1;

		for (int ti = 0; ti < totalSize; ++ti) {
			for (int tj = 0; tj < totalSize; ++tj) {
				int iMax = ti + size - 1;
				int jMax = tj + size - 1;
				for (int i = ti; i < iMax; ++i)
					total[ti][tj] += fuel[i][jMax];
				for (int j = tj; j < jMax; ++j)
					total[ti][tj] += fuel[iMax][j];
				total[ti][tj] += fuel[iMax][jMax];

				if (total[ti][tj] > max) {
					max = total[ti][tj];
					resultX = tj + 1;
					resultY = ti + 1;
					resultSize = size;
				}
			}
		}
	}

	printf("Result: %d,%d,%d\n", resultX, resultY, resultSize);

	return 0;
}
