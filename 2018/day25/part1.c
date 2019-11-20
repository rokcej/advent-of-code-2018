#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct _Coord {
	int x, y, z, w;
} Coord;

typedef struct _QueueEl {
	Coord *c;
	struct _QueueEl *next;
} QueueEl;

typedef struct _Queue {
	QueueEl *first;
	QueueEl *last;
} Queue;

Queue *newQueue() {
	Queue *q = malloc(sizeof(Queue));
	q->first = NULL;
	q->last = NULL;
	return q;
}

Coord *newCoord(int x, int y, int z, int w) {
	Coord *c = malloc(sizeof(Coord));
	c->x = x;
	c->y = y;
	c->z = z;
	c->w = w;
	return c;
}

void push(Coord *c, Queue *q) {
	QueueEl *el = malloc(sizeof(QueueEl));
	el->c = c;
	el->next = NULL;
	if (q->first == NULL) {
		q->first = el;
		q->last = el;
	} else {
		q->last->next = el;
		q->last = el;
	}
}

Coord *pop(Queue *q) {
	Coord *c;
	if (q->first == NULL) {
		c = NULL;
	} else if (q->first == q->last) {
		c = q->first->c;
		free(q->first);
		//free(q->last);
		q->first = NULL;
		q->last = NULL;
	} else {
		c = q->first->c;
		QueueEl *temp = q->first;
		q->first = q->first->next;
		free(temp);
	}
	return c;
}

int empty(Queue *q) {
	return (q->first == NULL);
}

void delete(Queue *q) {
	QueueEl *iter = q->first;
	while (iter != NULL) {
		QueueEl *temp = iter;
		iter = iter->next;
		free(temp->c);
		free(temp);
	}
	free(q);
}


typedef struct _Input {
	int value[4];
	struct _Input *next;
} Input;


int main() {
	// Read input
	int range[4][2] = {{INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}};
	int value[4];
	Input *list = malloc(sizeof(Input));
	Input *it = list;
	while (scanf("%d,%d,%d,%d\n", &value[0], &value[1], &value[2], &value[3]) == 4) {
		//printf("%d,%d,%d,%d\n", value[0], value[1], value[2], value[3]);
		it->next = malloc(sizeof(Input));
		it = it->next;
		memcpy(it->value, value, 4 * sizeof(int));
		for (int i = 0; i < 4; ++i) {
			if (value[i] < range[i][0])
				range[i][0] = value[i];

			if (value[i] > range[i][1])
				range[i][1] = value[ i];
		}
	}

	// Generate map
	int size[4];
	for (int i = 0; i < 4; ++i)
		size[i] = range[i][1] - range[i][0] + 1;

	int ****map = malloc(size[0] * sizeof(int***));
	for (int x = 0; x < size[0]; ++x) {
		map[x] = malloc(size[1] * sizeof(int**));
		for (int y = 0; y < size[1]; ++y) {
			map[x][y] = malloc(size[2] * sizeof(int*));
			for (int z = 0; z < size[2]; ++z) {
				map[x][y][z] = malloc(size[3] * sizeof(int));
				for (int w = 0; w < size[3]; ++w) {
					map[x][y][z][w] = 0;
				}
			}
		}
	}

	it = list->next;
	while (it != NULL) {
		map[ it->value[0] - range[0][0] ][ it->value[1] - range[1][0] ][ it->value[2] - range[2][0] ][ it->value[3] - range[3][0] ] = 1;
		it = it->next;
	}

	// Find constellations
	int result = 0;
	for (int x = 0; x < size[0]; ++x) {
		for (int y = 0; y < size[1]; ++y) {
			for (int z = 0; z < size[2]; ++z) {
				for (int w = 0; w < size[3]; ++w) {
					if (map[x][y][z][w] == 1) {
						map[x][y][z][w] = 2;
						++result;

						Queue *queue = newQueue();
						push(newCoord(x, y, z, w), queue);
						while (!empty(queue)) {
							Coord *c = pop(queue);
							
							for (int dx = -3; dx <= 3; ++dx) {
								for (int dy = -(3-abs(dx)); dy <= 3-abs(dx); ++dy) {
									for (int dz = -(3-abs(dx)-abs(dy)); dz <= 3-abs(dx)-abs(dy); ++dz) {
										for (int dw = -(3-abs(dx)-abs(dy)-abs(dz)); dw <= 3-abs(dx)-abs(dy)-abs(dz); ++dw) {
											int x2 = c->x + dx;
											int y2 = c->y + dy;
											int z2 = c->z + dz;
											int w2 = c->w + dw;
											if (x2 >= 0 && x2 < size[0] &&
												y2 >= 0 && y2 < size[1] &&
												z2 >= 0 && z2 < size[2] &&
												w2 >= 0 && w2 < size[3]) {
													if (map[x2][y2][z2][w2] == 1) {
														map[x2][y2][z2][w2] = 2;
														push(newCoord(x2, y2, z2, w2), queue);
													}
											}
										}
									}
								}
							}

							free(c);
						}
					}
				}
			}
		}
	}
	printf("Result: %d\n", result);

	return 0;
}
