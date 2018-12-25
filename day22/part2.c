#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

// 0 = Rocky, 1 = Wet, 2 = Narrow
// 0 = None, 1 = Torch, 2 = Gear
// Rocky = Gear or Torch, Wet = Gear or None, Narrow = Torch or None

enum Type { ROCKY = 0, WET, NARROW };
enum Tool { NONE = 0, TORCH, GEAR };

typedef struct _Map {
	int type;
	int cache[3];
} Map;

typedef struct _Node {
	int x, y;
	int tool;
	int count;
	struct _Node *next;
	struct _Node *prev;
} Node;

Node *newNode(int x, int y, int tool, int count) {
	Node *n = malloc(sizeof(Node));
	n->x = x;
	n->y = y;
	n->tool = tool;
	n->count = count;
	n->next = NULL;
	n->prev = NULL;
	return n;
}

void push(Node *n, Node **first) {
	if (*first != NULL) {
		(*first)->prev = n;
		n->next = *first;
	}
	*first = n;
}

void pop(Node **n, Node **first) {
	Node *prev = (*n)->prev;
	Node *next = (*n)->next;
	if (prev != NULL)
		prev->next = (*n)->next;
	if (next != NULL)
		next->prev = (*n)->prev;
	free(*n);

	if (*n == *first)
		*first = next;
	*n = next;
}

int adj[4][2] = {{0, -1}, {-1, 0}, {1, 0}, {0, 1}};

int main() {
	// Read input
	int depth, x0, y0;
	scanf("depth: %d\ntarget: %d,%d\n", &depth, &x0, &y0);

	// Make map
	int size = (x0 + y0 + 1) * 2;
	Map **map = malloc(size * sizeof(Map*));
	for (int y = 0; y < size; ++y) {
		map[y] = malloc(size * sizeof(Map));
		for (int x = 0; x < size; ++x) {
			if ((x == 0 && y == 0) || (x == x0 && y == y0))
				map[y][x].type = 0;
			else if (y == 0)
				map[y][x].type = x * 16807;
			else if (x == 0)
				map[y][x].type = y * 48271;
			else
				map[y][x].type = map[y][x-1].type * map[y-1][x].type;
			
			map[y][x].type = (map[y][x].type + depth) % 20183;
		}
	}
	for (int y = 0; y < size; ++y) {
		for (int x = 0; x < size; ++x) {
			map[y][x].type %= 3;
			map[y][x].cache[NONE] = INT_MAX;
			map[y][x].cache[TORCH] = INT_MAX;
			map[y][x].cache[GEAR] = INT_MAX;
		}
	}

	// Find quickest path
	int count = 0;
	Node *first = NULL;
	push(newNode(0, 0, TORCH, 0), &first);
	while (first != NULL) {
		int countMin = INT_MAX;
		for (Node *iter = first; iter != NULL; iter = iter->next) {
			if (iter->count < countMin)
				countMin = iter->count;
		}
		
		count = countMin;
		for (Node *iter = first; iter != NULL;) {
			if (map[iter->y][iter->x].cache[iter->tool] < iter->count) {
				pop(&iter, &first);
				continue;
			}

			if (iter->count == count) {
				if (iter->x == x0 && iter->y == y0) {
					if (iter->tool == TORCH) {
						printf("Result: %d\n", iter->count);
						return 0;
					} else {
						iter->tool = TORCH;
						iter->count += 7;
						continue;
					}
				}
				for (int i = 0; i < 4; ++i) {
					int x = iter->x + adj[i][0];
					int y = iter->y + adj[i][1];
					if (x >= 0 && y >= 0) {
						int countNew = count + 1;
						int toolNew = iter->tool;
						if (map[y][x].type == iter->tool) {
							countNew += 7;
							for (toolNew = 0; toolNew < 3; ++toolNew) {
								if (toolNew != map[y][x].type && toolNew != map[iter->y][iter->x].type)
									break;
							}
						}
						if (map[y][x].cache[toolNew] > countNew) {
							push(newNode(x, y, toolNew, countNew), &first);
							map[y][x].cache[toolNew] = countNew;
							for (int toolOther = 0; toolOther < 3; ++toolOther) {
								if (toolOther != toolNew && toolOther != map[y][x].type) {
									if (map[y][x].cache[toolOther] > countNew + 7)
										map[y][x].cache[toolOther] = countNew + 7;
									break;
								}
							}
						}
					}
				}
				pop(&iter, &first);
			} else {
				iter = iter->next;
			}
		}
	}

	return 0;
}
