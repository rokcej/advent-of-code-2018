#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 150
#define NUM_CARTS 17
#define NUM_DIR 4

enum dir { UP = 0, RIGHT, DOWN, LEFT };

typedef struct _Cart {
	int x;
	int y;
	char dir;
	int turns;
} Cart;

Cart newCart(int x, int y, char dir) {
	Cart c;
	c.x = x;
	c.y = y;
	c.dir = dir;
	c.turns = 0;
	return c;
}

int main() {
	// Generate map and carts from input
	Cart carts[NUM_CARTS];
	int cartsLen = 0;

	char map[SIZE][SIZE];
	for (int y = 0; y < SIZE; ++y) {
		for (int x = 0; x < SIZE; ++x) {
			char c = getchar();
			if (c == '<' || c == '>' || c == '^' || c == 'v') {
				carts[cartsLen].x = x;
				carts[cartsLen].y = y;
				carts[cartsLen].turns = 0;
				if (c == '<' || c == '>') {
					carts[cartsLen].dir = (c == '<' ? LEFT : RIGHT);
					map[y][x] = '-';
				} else {
					carts[cartsLen].dir = (c == '^' ? UP : DOWN);
					map[y][x] = '|';
				}
				cartsLen++;
			} else {
				map[y][x] = c;
			}
		}
		getchar(); // Consume newline
	}

	// Simulate ticks
	int dead[cartsLen];
	memset(dead, 0, cartsLen * sizeof(int));
	int num_dead = 0;
	int moved[cartsLen];
	while (1) {
		// Move carts
		memset(moved, 0, cartsLen * sizeof(int));
		while (1) {
			// Find next cart to move
			int i;
			for (i = 0; i < cartsLen; ++i) {
				if (!moved[i] && !dead[i])
					break;
			}
			if (i < cartsLen) {
				for (int j = i + 1; j < cartsLen; ++j) {
					if (!moved[j] && !dead[j] && (carts[j].y < carts[i].y || (carts[j].y == carts[i].y && carts[j].x < carts[i].x)))
						i = j;
				}
			} else {
				break;
			}
			// Move cart in current direction
			switch (carts[i].dir) {
				case LEFT:
				carts[i].x--;
				break;

				case RIGHT:
				carts[i].x++;
				break;

				case UP:
				carts[i].y--;
				break;

				case DOWN:
				carts[i].y++;
				break;
			}
			// Check for collisions
			for (int j = 0; j < cartsLen; ++j) {
				if (!dead[j] && i != j) {
					if (carts[i].x == carts[j].x && carts[i].y == carts[j].y) {
						dead[i] = 1;
						dead[j] = 1;
						num_dead += 2;
					}
				}
			}
			// Check for direction change
			switch (map[carts[i].y][carts[i].x]) {
				case '+':
				switch (carts[i].turns % 3) {
					case 0:
					carts[i].dir--;
					if (carts[i].dir < 0)
						carts[i].dir += NUM_DIR;
					break;
					case 1:
					break;
					case 2:
					carts[i].dir++;
					if (carts[i].dir >= NUM_DIR)
						carts[i].dir -= NUM_DIR;
					break;
				}
				carts[i].turns++;
				break;

				case '/':
				carts[i].dir = (NUM_DIR - carts[i].dir + 1) % NUM_DIR;
				break;

				case '\\':
				carts[i].dir = NUM_DIR - carts[i].dir - 1;
				break;
			}
			moved[i] = 1;
		}
		// Check if last alive
		if (cartsLen - num_dead == 1) {
			for (int i = 0; i < cartsLen; ++i) {
				if (!dead[i]) {
					printf("Result: %d,%d\n", carts[i].x, carts[i].y);
					return 0;
				}
			}
		}
	}

	return 0;
}
