#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct _Water {
	int x, y;
} Water;

typedef struct _QueueEl {
	Water *w;
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

Water *newWater(int x, int y) {
	Water *w = malloc(sizeof(Water));
	w->x = x;
	w->y = y;
	return w;
}

void push(Water *w, Queue *q) {
	QueueEl *el = malloc(sizeof(QueueEl));
	el->w = w;
	el->next = NULL;
	if (q->first == NULL) {
		q->first = el;
		q->last = el;
	} else {
		q->last->next = el;
		q->last = el;
	}
}

Water *pop(Queue *q) {
	Water *w;
	if (q->first == NULL) {
		w = NULL;
	} else if (q->first == q->last) {
		w = q->first->w;
		free(q->first);
		q->first = NULL;
		q->last = NULL;
	} else {
		w = q->first->w;
		QueueEl *temp = q->first;
		q->first = q->first->next;
		free(temp);
	}
	return w;
}

int empty(Queue *q) {
	return (q->first == NULL);
}

void delete(Queue *q) {
	QueueEl *iter = q->first;
	while (iter != NULL) {
		QueueEl *temp = iter;
		iter = iter->next;
		free(temp->w);
		free(temp);
	}
	free(q);
}

typedef struct _Input {
	char single;
	int singleVal;
	char range;
	int rangeMin;
	int rangeMax;
	struct _Input *next;
} Input;

Input *newInput(char single, int singleVal, char range, int rangeMin, int rangeMax) {
	Input *in = malloc(sizeof(Input));
	in->single = single;
	in->singleVal = singleVal;
	in->range = range;
	in->rangeMin = rangeMin;
	in->rangeMax = rangeMax;
	in->next = NULL;
	return in;
}

int xMin = INT_MAX, xMax = INT_MIN;
int yMin = INT_MAX, yMax = INT_MIN;
char **map;

void printMap() {
	for (int y = yMin-1; y <= yMax+1; ++y) {
		for (int x = xMin-1; x <= xMax+1; ++x) {
			printf("%c", map[y][x]);
		}
		printf("\n");
	}
	fflush(stdout);
}

int main() {
	// Read input
	Input *first = NULL;
	Input *iter = first;
	char single;
	while ((single = getchar()) == 'x' || single == 'y') {
		char range;
		int singleVal, rangeMin, rangeMax;
		scanf("=%d, %c=%d..%d\n", &singleVal, &range, &rangeMin, &rangeMax);
		
		Input *in = newInput(single, singleVal, range, rangeMin, rangeMax);
		if (iter == NULL) {
			first = in;
			iter = first;
		} else {
			iter->next = in;
			iter = iter->next;
		}

		if (single == 'x') {
			if (singleVal < xMin) xMin = singleVal;
			if (singleVal > xMax) xMax = singleVal;

			if (rangeMin < yMin) yMin = rangeMin;
			if (rangeMax > yMax) yMax = rangeMax;
		} else {
			if (singleVal < yMin) yMin = singleVal;
			if (singleVal > yMax) yMax = singleVal;

			if (rangeMin < xMin) xMin = rangeMin;
			if (rangeMax > xMax) xMax = rangeMax;
		}
	}
	
	// Generate map from input
	int width = xMax - xMin + 3, height = yMax - yMin + 3;
	int xOffset = xMin - 1, yOffset = yMin - 1;
	map = malloc(height * sizeof(char*));
	for (int i = 0; i < height; ++i) {
		map[i] = malloc(width * sizeof(char));
		memset(map[i], '.', width * sizeof(char));
		map[i] -= xOffset;
	}
	map -= yOffset;

	iter = first;
	while (iter != NULL) {
		if (iter->single == 'x') {
			for (int y = iter->rangeMin; y <= iter->rangeMax; ++y)
				map[y][iter->singleVal] = '#';
		} else {
			for (int x = iter->rangeMin; x <= iter->rangeMax; ++x)
				map[iter->singleVal][x] = '#';
		}
		iter = iter->next;
	}

	// Simulate
	int xSrc = 500, ySrc = yMin - 1;
	Queue *queue = newQueue();
	Queue *waiting = newQueue();

	int gain;
	do {
		// Add water source element
		map[ySrc][xSrc] = '|';
		push(newWater(xSrc, ySrc), queue);
		gain = 1;

		while (!empty(queue)) {
			Water *w = pop(queue);
			int x = w->x;
			int y = w->y;

			if (map[y][x] != '~') {
				if (map[y+1][x] == '.') {
					map[y][x] = '.';
					if (y+1 <= yMax) {
						map[y+1][x] = '|';
						push(newWater(x, y+1), waiting);
					} else {
						--gain;
					}
				} else if (map[y+1][x] == '|') {
					map[y][x] = '.';
					gain--;
				} else if (map[y+1][x] == '~' || map[y+1][x] == '#') {
					int left = 0, right = 0;
					if (map[y][x-1] == '.') {
						left = 1;
						map[y][x] = '.';
						map[y][x-1] = '|';
						push(newWater(x-1, y), waiting);
						++gain;
					}
					if (map[y][x+1] == '.') {
						right = 1;
						map[y][x] = '.';
						map[y][x+1] = '|';
						push(newWater(x+1, y), waiting);
						++gain;
					}
					if (!left && !right) {
						left = 0;
						right = 0;
						int l = x, r = x;
						if (map[y][x-1] == '#' || map[y][x-1] == '|') {
							while (map[y][r] == '|' && (map[y+1][r] == '#' || map[y+1][r] == '~')) {
								if (map[y][r+1] == '#') {
									right = 1;
									break;
								}
								++r;
							}
						}
						if (map[y][x+1] == '#' || map[y][x-1] == '|') {
							while (map[y][l] == '|' && (map[y+1][l] == '#' || map[y+1][l] == '~')) {
								if (map[y][l-1] == '#') {
									left = 1;
									break;
								}
								--l;
							}
						}
						if (left && right) {
							for (int i = l; i <= r; ++i)
								map[y][i] = '~';
						}
					} else {
						--gain;
					}
				}
			}
			free(w);
		}
		// Swap queues
		Queue *temp = queue;
		queue = waiting;
		waiting = temp;
	} while (gain > 0);

	// Count result
	int result = 0;
	for (int y = yMin; y <= yMax; ++y) {
		for (int x = xMin-1; x <= xMax+1; ++x) {
			if (map[y][x] == '|' || map[y][x] == '~') {
				++result;
			}
		}
	}
	printf("Result: %d\n", result);
	
	//printMap();

	return 0;
}
