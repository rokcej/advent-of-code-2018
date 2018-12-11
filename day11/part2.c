#include <stdio.h>

#define SIZE 300

int main() {
	int serial;
	scanf("%d", &serial);

	int sums[SIZE+1][SIZE+1] = { 0 }; // Summed-area table
	for (int y = 1; y <= SIZE; ++y) {
		for (int x = 1; x <= SIZE; ++x) {
			int rack = x + 10;
			int power = (rack * y + serial) * rack / 100 % 10 - 5;
			sums[y][x] = power + sums[y][x-1] + sums[y-1][x] - sums[y-1][x-1];
		}
	}

	int xMax, yMax, sizeMax;
	int max = -6; // Min value for single cell is -5
	for (int size = 1; size <= SIZE; ++size) {
		for (int y = 1; y <= SIZE - size + 1; ++y) {
			for (int x = 1; x <= SIZE - size + 1; ++x) {
				int total = sums[y+size-1][x+size-1] - sums[y+size-1][x-1] - sums[y-1][x+size-1] + sums[y-1][x-1];
				if (total > max) {
					max = total;
					xMax = x;
					yMax = y;
					sizeMax = size;
				}
			}
		}
	}
	printf("Result: %d,%d,%d\n", xMax, yMax, sizeMax);

	return 0;
}
