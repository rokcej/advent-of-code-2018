#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define LEN 1000

typedef struct _Bot {
	int x, y, z;
	int r;
} Bot;

int min(int a, int b) {
	return (a < b ? a : b);
}

int max(int a, int b) {
	return (a > b ? a : b);
}

int man(int x, int y, int z, int x2, int y2, int z2) {
	return abs(x2 - x) + abs(y2 - y) + abs(z2 - z);
}


// Priority Queue
typedef struct _Box {
	int xMin, xMax;
	int yMin, yMax;
	int zMin, zMax;
	int count;
} Box;

typedef struct _QueueEl {
	Box *el;
	struct _QueueEl *next;
} QueueEl;

typedef struct _Queue {
	QueueEl *first;
	QueueEl *last;
} Queue;

Queue *newQueue() {
	Queue *q = malloc(sizeof(Queue));
	q->first = NULL;
	return q;
}

Box *newBox(int xMin, int xMax, int yMin, int yMax, int zMin, int zMax, int count) {
	Box *el = malloc(sizeof(Box));
	el->xMin = xMin;
	el->xMax = xMax;
	el->yMin = yMin;
	el->yMax = yMax;
	el->zMin = zMin;
	el->zMax = zMax;
	el->count = count;
	return el;
}

int compare(Box *b1, Box *b2) {
	if (b1->count < b2->count) {
		return -1;
	} else if (b1->count > b2->count) {
		return 1;
	} else {
		int dist1 = man(min(abs(b1->xMin), abs(b1->xMax)), min(abs(b1->yMin), abs(b1->yMax)), min(abs(b1->zMin), abs(b1->zMax)), 0, 0, 0);
		int dist2 = man(min(abs(b2->xMin), abs(b2->xMax)), min(abs(b2->yMin), abs(b2->yMax)), min(abs(b2->zMin), abs(b2->zMax)), 0, 0, 0);
		if (dist1 > dist2) {
			return -1;
		} else if (dist1 < dist2) {
			return -1;
		} else {
			return 0;
		}
	}
}

void push(Box *el, Queue *q) {
	QueueEl *qel = malloc(sizeof(QueueEl));
	qel->el = el;
	qel->next = NULL;
	if (q->first == NULL) {
		q->first = qel;
	} else if (compare(qel->el, q->first->el) >= 0) {
		qel->next = q->first;
		q->first = qel;
	} else {
		QueueEl *iter = q->first;
		while (iter->next != NULL && compare(qel->el, iter->next->el) < 0)
			iter = iter->next;
		qel->next = iter->next;
		iter->next = qel;
	}
}

Box *pop(Queue *q) {
	Box *el;
	if (q->first == NULL) {
		el = NULL;
	} else if (q->first == q->last) {
		el = q->first->el;
		free(q->first);
		q->first = NULL;
		q->last = NULL;
	} else {
		el = q->first->el;
		QueueEl *temp = q->first;
		q->first = q->first->next;
		free(temp);
	}
	return el;
}

int empty(Queue *q) {
	return (q->first == NULL);
}

void delete(Queue *q) {
	QueueEl *iter = q->first;
	while (iter != NULL) {
		QueueEl *temp = iter;
		iter = iter->next;
		free(temp->el);
		free(temp);
	}
	free(q);
}


int main() {
	// Read input
	Bot bots[LEN];
	int xMin = INT_MAX, yMin = INT_MAX, zMin = INT_MAX;
	int xMax = INT_MIN, yMax = INT_MIN, zMax = INT_MIN;
	for (int i = 0; i < LEN; ++i) {
		scanf("pos=<%d,%d,%d>, r=%d\n", &bots[i].x, &bots[i].y, &bots[i].z, &bots[i].r);
		if (bots[i].x < xMin) xMin = bots[i].x;
		if (bots[i].y < yMin) yMin = bots[i].y;
		if (bots[i].z < zMin) zMin = bots[i].z;

		if (bots[i].x > xMax) xMax = bots[i].x;
		if (bots[i].y > yMax) yMax = bots[i].y;
		if (bots[i].z > zMax) zMax = bots[i].z;
	}

	int dimMax = max(max(xMax-xMin, yMax-yMin), zMax-zMin) + 1;
	int sizeMax = 1;
	while (sizeMax < dimMax)
		sizeMax <<= 1;

	// Find result
	int result = -1;
	Queue *queue = newQueue();
	push(newBox(xMin, xMin + sizeMax-1, yMin, yMin + sizeMax-1, zMin, zMin + sizeMax-1, LEN), queue);
	while (!empty(queue)) {
		Box *box = pop(queue);
		int size = box->xMax - box->xMin + 1;
		if (size == 1) {
			result = man(box->xMin, box->yMin, box->zMin, 0, 0, 0);
			break;
		}

		size >>= 1;

		for (int xPart = 0; xPart <= 1; ++xPart) {
			for (int yPart = 0; yPart <= 1; ++yPart) {
				for (int zPart = 0; zPart <= 1; ++zPart) {
					int xMin = box->xMin + xPart * size;
					int yMin = box->yMin + yPart * size;
					int zMin = box->zMin + zPart * size;

					int xMax = box->xMax - (1-xPart) * size;
					int yMax = box->yMax - (1-yPart) * size;
					int zMax = box->zMax - (1-zPart) * size;

					int count = 0;
					for (int i = 0; i < LEN; ++i) {
						int x = bots[i].x;
						int y = bots[i].y;
						int z = bots[i].z;
						int r = bots[i].r;

						// Points in box nearest to bot
						int x2, y2, z2; 

						if (x < xMin) x2 = xMin;
						else if (x > xMax) x2 = xMax;
						else x2 = x;

						if (y < yMin) y2 = yMin;
						else if (y > yMax) y2 = yMax;
						else y2 = y;

						if (z < zMin) z2 = zMin;
						else if (z > zMax) z2 = zMax;
						else z2 = z;

						int dist = man(x, y, z, x2, y2, z2);
						if (dist <= r)
							++count;
					}
					push(newBox(xMin, xMax, yMin, yMax, zMin, zMax, count), queue);
				}
			}
		}
		free(box);
	}
	printf("Result: %d\n", result);

	return 0;
}
