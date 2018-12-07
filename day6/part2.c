#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LEN 50
#define DIST_MAX 10000

int main() {
	int xMin = -1, xMax = -1, yMin = -1, yMax = -1;

	int coords[LEN][2];
	int i = 0;
	while (scanf("%d, %d\n", coords[i]+0, coords[i]+1) != EOF) {
		int x = coords[i][0];
		int y = coords[i][1];

		if (xMin == -1 || x < xMin)
			xMin = x;
		if (xMax == -1 || x > xMax)
			xMax = x;
		if (yMin == -1 || y < yMin)
			yMin = y;
		if (yMax == -1 || y > yMax)
			yMax = y;
		
		i++;
	}

	for (i = 0; i < LEN; i++) {
		coords[i][0] -= xMin;
		coords[i][1] -= yMin;
	}

	xMax -= xMin;
	xMin = 0;
	yMax -= yMin;
	yMin = 0;

	int width = xMax - (xMin) + 1;
	int height = yMax - (yMin) + 1;

	int result = 0;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			int distSum = 0;
			for (int i = 0; i < LEN; i++) {
				int dist = abs(x - coords[i][0]) + abs(y - coords[i][1]);
				distSum += dist;
			}
			if (distSum < DIST_MAX)
				result++;
		}
	}

	printf("Result: %d\n", result);

	return 0;
}
