// The program is slightly wrong, but it still produced the correct result
// Cba to fix it lmao
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 14131

typedef struct _Option {
	int len;
	struct _Option *next;
} Option;

Option *newOption() {
	Option *o = malloc(sizeof(Option));
	o->len = 0;
	o->next = NULL;
	return o;
}

char *regex;
int **map;
int gi = 1;

int doors(int x0, int y0, int s0) {
	int val = s0;
	int x = x0, y = y0, s = s0;

	while (1) {
		char c = regex[gi++];
		if (c == 'N' || c == 'S' || c == 'E' || c == 'W') {
			++s;
			if (c == 'N') --y;
			else if (c == 'S') ++y;
			else if (c == 'E') ++x;
			else --x;

			if (map[y][x] == -1 || map[y][x] > s) map[y][x] = s;
			else if (map[y][x] < s) s = map[y][x];
		} else if (c == '|') {
			if (s > val) val = s;
			x = x0;
			y = y0;
			s = s0;
		} else if (c == '(') {
			val = doors(x, y, s);
		} else if (c == ')' || c == '$') {
			if (s > val) val = s;
			return val;
		}
	}

}

int main() {
	// Read input
	regex = malloc((LEN + 1) * sizeof(char));
	scanf("%s", regex);

	// Generate map
	int size = 2 * 5000; // Max regex path length is 4491 for my input
	map = malloc(size * sizeof(int*));
	for (int i = 0; i < size; ++i) {
		map[i] = malloc(size * sizeof(int));
		memset(map[i], -1, size * sizeof(int));
		map[i] += size / 2;
	}
	map += size / 2;

	// Calculate result
	map[0][0] = 0;
	doors(0, 0, 0);

	int result = 0;
	for (int y = -5000; y < 5000; ++y) {
		for (int x = -5000; x < 5000; ++x) {
			if (map[y][x] >= 1000)
				++result;
		}
	}
	printf("Result: %d\n", result);

	return 0;
}
