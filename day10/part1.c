#include <stdio.h>
#include <string.h>

#define LEN 379

#define MAX_WIDTH 80
#define MAX_HEIGHT 22

typedef struct _Point {
	int x;
	int y;
	int dx;
	int dy;
} Point;

int main() {
	Point points[LEN];
	for (int i = 0; i < LEN; ++i)
		scanf("position=<%d, %d> velocity=<%d, %d>\n", &(points[i].x), &(points[i].y), &(points[i].dx), &(points[i].dy));

	int xMin, xMax;
	int yMin, yMax;

	// Simulate until all points are within boundaries
	do {
		for (int i = 0; i < LEN; ++i) {
			points[i].x += points[i].dx;
			points[i].y += points[i].dy;

			if (i == 0) {
				xMin = points[i].x; xMax = points[i].x;
				yMin = points[i].y; yMax = points[i].y;
			} else {
				if (points[i].x < xMin)
					xMin = points[i].x;
				else if (points[i].x > xMax)
					xMax = points[i].x;

				if (points[i].y < yMin)
					yMin = points[i].y;
				else if (points[i].y > yMax)
					yMax = points[i].y;
			}
		}
	} while (yMax - yMin > MAX_HEIGHT || xMax - xMin > MAX_WIDTH);

	// Display all outputs within boundaries
	do {
		// Output
		int width = xMax - xMin + 1;
		int height = yMax - yMin + 1;

		char grid[height][width];
		memset(&grid[0][0], ' ', height * width * sizeof(char));

		int xOffset = xMin;
		int yOffset = yMin;

		for (int i = 0; i < LEN; ++i)
			grid[points[i].y - yOffset][points[i].x - xOffset] = '#';

		for (int i = 0; i < width; ++i)
			printf("-");
		printf("\n");
		for (int y = 0; y < height; ++y) {
			for (int x = 0; x < width; ++x) {
				printf("%c", grid[y][x]);
			}
			printf("\n");
		}
		for (int i = 0; i < width; ++i)
			printf("-");
		printf("\n");

		// Next step
		for (int i = 0; i < LEN; ++i) {
			points[i].x += points[i].dx;
			points[i].y += points[i].dy;

			if (i == 0) {
				xMin = points[i].x; xMax = points[i].x;
				yMin = points[i].y; yMax = points[i].y;
			} else {
				if (points[i].x < xMin)
					xMin = points[i].x;
				else if (points[i].x > xMax)
					xMax = points[i].x;

				if (points[i].y < yMin)
					yMin = points[i].y;
				else if (points[i].y > yMax)
					yMax = points[i].y;
			}
		}

	} while (yMax - yMin <= MAX_HEIGHT && xMax - xMin <= MAX_WIDTH);

	return 0;
}
