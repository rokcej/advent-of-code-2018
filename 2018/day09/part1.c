#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Marble {
	int id;
	struct _Marble *next;
	struct _Marble *prev;
} Marble;

Marble *newMarble(int id) {
	Marble *m = malloc(sizeof(Marble));
	m->id = id;
	m->next = NULL;
	m->prev = NULL;
	return m;
}

int main() {
	int nPlayers, lastPoints;
	scanf("%d players; last marble is worth %d points\n", &nPlayers, &lastPoints);

	int scores[nPlayers];
	memset(scores, 0, nPlayers * sizeof(int));

	int pid = 0;
	int mid = 0;

	Marble *marbles = newMarble(mid++);
	marbles->next = marbles;
	marbles->prev = marbles;

	while (mid <= lastPoints) {
		if (mid % 23 == 0) {
			int score = mid;
			for (int i = 0; i < 7 - 1; i++)
				marbles = marbles->prev;

			Marble *old = marbles->prev;
			score += old->id;
			marbles->prev = old->prev;
			old->prev->next = marbles;
			free(old);
			scores[pid] += score;
		} else {
			marbles = marbles->next;
			Marble *new = newMarble(mid);
			new->prev = marbles;
			new->next = marbles->next;
			marbles->next->prev = new;
			marbles->next = new;
			marbles = marbles->next;
		}

		pid++;
		pid %= nPlayers;
		mid++;
	}

	int result = scores[0];
	for (int i = 1; i < nPlayers; ++i) {
		if (result < scores[i])
			result = scores[i];
	}
	printf("Result: %d\n", result);

	return 0;
}
