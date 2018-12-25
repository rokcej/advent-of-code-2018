#include <stdio.h>
#include <stdlib.h>

int main() {
	int depth, x0, y0;
	scanf("depth: %d\ntarget: %d,%d\n", &depth, &x0, &y0);

	int result = 0;

	int **map = malloc((y0+1) * sizeof(int*));
	for (int y = 0; y <= y0; ++y) {
		map[y] = malloc((x0+1) * sizeof(int));
		for (int x = 0; x <= x0; ++x) {
			if ((x == 0 && y == 0) || (x == x0 && y == y0))
				map[y][x] = 0;
			else if (y == 0)
				map[y][x] = x * 16807;
			else if (x == 0)
				map[y][x] = y * 48271;
			else
				map[y][x] = map[y][x-1] * map[y-1][x];
			
			map[y][x] = (map[y][x] + depth) % 20183;
			result += map[y][x] % 3;
		}
	}
	printf("Result: %d\n", result);

	return 0;
}
