#include <stdio.h>
#include <stdlib.h>

#define EMPTY 0
#define OVERLAP -1

int main() {
	//int fabric[1000][1000] = { { EMPTY } };
	int **fabric = malloc(1000 * sizeof(int*));
	for (int i = 0; i < 1000; i++) {
		fabric[i] = malloc(1000 * sizeof(int));
		for (int j = 0; j < 1000; j++)
			fabric[i][j] = EMPTY;
	}

	int count = 0;
	int id, x0, y0, w, h;
	while (scanf("#%d @ %d,%d: %dx%d\n", &id, &x0, &y0, &w, &h) != EOF) {
		for (int y = y0; y < y0 + h; y++) {
			for (int x = x0; x < x0 + w; x++) {
				if (fabric[y][x] == EMPTY) {
					fabric[y][x] = id;
				} else if (fabric[y][x] != OVERLAP) {
					fabric[y][x] = OVERLAP;
					count++;
				}
			}
		}
	}

	printf("Result: %d\n", count);
	return 0;
}
