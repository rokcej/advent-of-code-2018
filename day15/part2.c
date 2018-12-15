#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 32

typedef struct _Unit {
	int lastRound;
	int hp;
	int atk;
} Unit;

typedef struct _Move {
	int x0, y0;
	int x, y;
} Move;

typedef struct _QueueEl {
	Move *m;
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

Move *newMove(int x, int y, int x0, int y0) {
	Move *m = malloc(sizeof(Move));
	m->x = x;
	m->y = y;
	m->x0 = x0;
	m->y0 = y0;
	return m;
}

void push(Move *m, Queue *q) {
	QueueEl *el = malloc(sizeof(QueueEl));
	el->m = m;
	el->next = NULL;
	if (q->first == NULL) {
		q->first = el;
		q->last = el;
	} else {
		q->last->next = el;
		q->last = el;
	}
}

Move *pop(Queue *q) {
	Move *m;
	if (q->first == NULL) {
		m = NULL;
	} else if (q->first == q->last) {
		m = q->first->m;
		free(q->first);
		//free(q->last);
		q->first = NULL;
		q->last = NULL;
	} else {
		m = q->first->m;
		QueueEl *temp = q->first;
		q->first = q->first->next;
		free(temp);
	}
	return m;
}

int empty(Queue *q) {
	return (q->first == NULL);
}

void delete(Queue *q) {
	QueueEl *iter = q->first;
	while (iter != NULL) {
		QueueEl *temp = iter;
		iter = iter->next;
		free(temp->m);
		free(temp);
	}
	free(q);
}

Unit *newUnit() {
	Unit *u = malloc(sizeof(Unit));
	u->lastRound = -1;
	u->hp = 200;
	u->atk = 3;
	return u;
}

void printMap(char map[SIZE][SIZE]) {
	for (int y = 0; y < SIZE; ++y) {
		for (int x = 0; x < SIZE; ++x) {
			printf("%c", map[y][x]);
		}
		printf("\n");
	}
}

int main() {
	// Read input
	int elves_start = 0;
	int goblins_start = 0;
	char map_start[SIZE][SIZE] = { 0 };
	for (int y = 0; y < SIZE; ++y) {
		for (int x = 0; x < SIZE; ++x) {
			map_start[y][x] = getchar();
			if (map_start[y][x] == 'E')
				++elves_start;
			else if (map_start[y][x] == 'G')
				++goblins_start;
		}
		getchar(); // Consume newline
	}

	// Find lowest atk
	int result = 0;
	for (int atk = 4; 1; ++atk) {
		// Refresh values
		int elves = elves_start;
		int goblins = goblins_start;
		char map[SIZE][SIZE];
		memcpy(&map[0][0], &map_start[0][0], SIZE * SIZE * sizeof(char));
		Unit *units[SIZE][SIZE] = { NULL };
		// Change elf atk
		for (int y = 0; y < SIZE; ++y) {
			for (int x = 0; x < SIZE; ++x) {
				if (map[y][x] == 'E' || map[y][x] == 'G') {
					units[y][x] = newUnit();
					if (map[y][x] == 'E') {
						units[y][x]->atk = atk;
					}
				}
			}
		}

		// Simulate battle
		for (int r = 0; 1; ++r) {
			int end = 0;
			for (int y = 0; y < SIZE; ++y) {
				for (int x = 0; x < SIZE; ++x) {
					if ((map[y][x] == 'E' || map[y][x] == 'G') && units[y][x]->lastRound < r) {

						Unit *u = units[y][x];
						u->lastRound = r;
						char self = map[y][x];
						char target = (self == 'E' ? 'G' : 'E');

						int attacked = 0;
						int moved = 0;
						int adj[4][2] = {{0, -1}, {-1, 0}, {1, 0}, {0, 1}};
						// Attack if in range
						{
							Unit *u2 = NULL;
							int x_u2;
							int y_u2;
							for (int i = 0; i < 4; ++i) {
								int x2 = x + adj[i][0];
								int y2 = y + adj[i][1];
								if (x2 >= 0 && x2 < SIZE && y2 >= 0 && y2 < SIZE) {
									if (map[y2][x2] == target) {
										if (u2 == NULL || units[y2][x2]->hp < u2->hp) {
											u2 = units[y2][x2];
											x_u2 = x2;
											y_u2 = y2;
										}
									}
								}
							}
							if (u2 != NULL) {
								u2->hp -= u->atk;
								if (u2->hp <= 0) {
									map[y_u2][x_u2] = '.';
									units[y_u2][x_u2] = NULL;
									if (target == 'E')
										--elves;
									else if (target == 'G')
										--goblins;
									free(u2);
								}
								attacked = 1;
							}
						}
						// Move and attack
						if (!attacked) {
							// Move
							Queue *q = newQueue();
							int current = 0;
							int next = 0;

							int visited[SIZE][SIZE] = { 0 };
							/*int **visited = malloc(SIZE * sizeof(int*));
							for (int idx = 0; idx < SIZE; ++idx) {
								visited[idx] = malloc(SIZE * sizeof(int));
								memset(visited[idx], 0, SIZE * sizeof(int));
							}
							visited[y][x] = 1;*/

							for (int i = 0; i < 4; ++i) {
								int x2 = x + adj[i][0];
								int y2 = y + adj[i][1];
								push(newMove(x2, y2, x2, y2), q);
								++next;
							}
							Move *path = NULL;

							while (!empty(q)) {
								if (current <= 0) {
									if (path != NULL) {
										break;
									} else {
										current = next;
										next = 0;
									}
								}
								--current;
								Move *m = pop(q);
								int x2 = m->x;
								int y2 = m->y;
								if (x2 >= 0 && x2 < SIZE && y2 >= 0 && y2 < SIZE && !visited[y2][x2]) {
									visited[y2][x2] = 1;
									if (map[y2][x2] == '.') {
										int adjacentToTarget = 0;
										for (int i = 0; i < 4; ++i) {
											int x3 = x2 + adj[i][0];
											int y3 = y2 + adj[i][1];
											if (x3 >= 0 && x3 < SIZE && y3 >= 0 && y3 < SIZE) {
												if (map[y3][x3] == target) {
													adjacentToTarget = 1;
													break;
												}
											}
										}
										if (adjacentToTarget) {
											if (path == NULL) {
												path = m;
												continue;
											} else if (y2 < path->y || (y2 == path->y && x2 < path->x)) {
												free(path);
												path = m;
												continue;
											}
										} else {
											for (int i = 0; i < 4; ++i) {
												int x3 = x2 + adj[i][0];
												int y3 = y2 + adj[i][1];
												push(newMove(x3, y3, m->x0, m->y0), q);
												++next;
											}
										}
									}
								}
								free(m);
							}
							
							/*for (int idx = 0; idx < SIZE; ++idx)
								free(visited[idx]);
							free(visited);
							delete(q);*/

							if (path != NULL) {
								int x2 = path->x0;
								int y2 = path->y0;

								map[y2][x2] = self;
								map[y][x] = '.';

								units[y2][x2] = u;
								units[y][x] = NULL;

								free(path);
								moved = 1;

								// Attack if now in range
								Unit *u3 = NULL;
								int x_u3;
								int y_u3;
								for (int i = 0; i < 4; ++i) {
									int x3 = x2 + adj[i][0];
									int y3 = y2 + adj[i][1];
									if (x3 >= 0 && x3 < SIZE && y3 >= 0 && y3 < SIZE) {
										if (map[y3][x3] == target) {
											if (u3 == NULL || units[y3][x3]->hp < u3->hp) {
												u3 = units[y3][x3];
												x_u3 = x3;
												y_u3 = y3;
											}
										}
									}
								}
								if (u3 != NULL) {
									u3->hp -= u->atk;
									if (u3->hp <= 0) {
										map[y_u3][x_u3] = '.';
										units[y_u3][x_u3] = NULL;
										if (target == 'E')
											--elves;
										else if (target == 'G')
											--goblins;
										free(u3);
									}
									attacked = 1;
								}
							}
						}

						if (!moved && !attacked && (elves == 0 || goblins == 0)) {
							end = 1;
							break;
						}
					}
				}
				if (end)
					break;
			}

			if (end) {
				int sum = 0;
				for (int y = 0; y < SIZE; ++y) {
					for (int x = 0; x < SIZE; ++x) {
						if (map[y][x] == 'E' || map[y][x] == 'G') {
							sum += units[y][x]->hp;
						}
					}
				}
				result = r * sum;
				break;
			}
		}
		// Free memory
		for (int y = 0; y < SIZE; ++y) {
			for (int x = 0; x < SIZE; ++x) {
				if (map[y][x] == 'E' || map[y][x] == 'G') {
					free(units[y][x]);
				}
			}
		}

		if (elves == elves_start)
			break;
	}
	printf("Result: %d\n", result);

	return 0;
}
