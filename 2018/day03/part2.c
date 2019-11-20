#include <stdio.h>
#include <stdlib.h>

#define EMPTY 0
#define OVERLAP -1
#define ID_LEN 1349

int main() {
	int **fabric = malloc(1000 * sizeof(int*));
	for (int i = 0; i < 1000; i++) {
		fabric[i] = malloc(1000 * sizeof(int));
		for (int j = 0; j < 1000; j++)
			fabric[i][j] = EMPTY;
	}

	int ids[ID_LEN + 1] = { 0 };

	int count = 0;
	int id, x0, y0, w, h;
	int idx = 1;
	while (scanf("#%d @ %d,%d: %dx%d\n", &id, &x0, &y0, &w, &h) != EOF) {
		for (int y = y0; y < y0 + h; y++) {
			for (int x = x0; x < x0 + w; x++) {
				if (fabric[y][x] == EMPTY) {
					fabric[y][x] = id;
				} else if (fabric[y][x] != OVERLAP) {
					ids[fabric[y][x]] = OVERLAP;
					ids[idx] = OVERLAP;
					fabric[y][x] = OVERLAP;
					count++;
				} else {
					ids[idx] = OVERLAP;
				}
			}
		}
		idx++;
	}

	int result = 0;
	for (int i = 1; i < ID_LEN + 1; i++) {
		if (ids[i] != OVERLAP) {
			result = i;
			break;
		}
	}

	printf("Result: %d\n", result);
	return 0;
}
