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

	lastPoints *= 100;

	long long scores[nPlayers];
	memset(scores, 0, nPlayers * sizeof(long long));

	int pid = 0;
	int mid = 0;

	Marble *marbles = newMarble(mid++);
	marbles->next = marbles;
	marbles->prev = marbles;

	while (mid <= lastPoints) {
		if (mid % 23 == 0) {
			for (int i = 0; i < 7 - 1; i++)
				marbles = marbles->prev;

			Marble *old = marbles->prev;

			scores[pid] += mid;
			scores[pid] += old->id;

			marbles->prev = old->prev;
			old->prev->next = marbles;
			free(old);
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

	long long result = scores[0];
	for (int i = 1; i < nPlayers; ++i) {
		if (result < scores[i])
			result = scores[i];
	}
	printf("Result: %lld\n", result);

	return 0;
}
