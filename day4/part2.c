#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 976
#define SLEEP -1
#define WAKE_UP -2

typedef struct _Guard {
	int id;
	int asleep[60];
	int max_minutes;
	int i_max_minutes;
	struct _Guard *next;
} Guard;

Guard *new_guard(int id) {
	Guard *g = malloc(sizeof(Guard));
	g->id = id;
	g->max_minutes = 0;
	g->i_max_minutes = 0;
	g->next = NULL;
	memset(g->asleep, 0, 60 * sizeof(int));

	return g;
}

int get_minute(char date[17]) {
	return atoi(date + 14);
}

int main() {
	char dates[LEN][17];
	int actions[LEN];

	for (int i = 0; i < LEN; ++i) {
		char date_time[6];
		char text[8];
		char dump[8];

		scanf("[%10s %5s] %s %s", dates[i], date_time, dump, text);
		strcat(dates[i], " ");
		strcat(dates[i], date_time);

		if (strcmp(text, "asleep") == 0) {
			actions[i] = SLEEP;
		} else if (strcmp(text, "up") == 0) {
			actions[i] = WAKE_UP;
		} else {
			actions[i] = atoi(text + 1);
		}

		int j = i;
		while (j > 0 && strcmp(dates[j], dates[j-1]) < 0) {
			char date_temp[17];
			strcpy(date_temp, dates[j-1]);
			strcpy(dates[j-1], dates[j]);
			strcpy(dates[j], date_temp);

			int id_temp = actions[j-1];
			actions[j-1] = actions[j];
			actions[j] = id_temp;
			j--;
		}

		while (getchar() != '\n'); // Move to the next line
	}

	Guard *first = NULL;
	Guard *current = NULL;

	int sleep_minute, wake_up_minute;

	for (int i = 0; i < LEN; ++i) {
		if (actions[i] == SLEEP) {
			sleep_minute = get_minute(dates[i]);
		} else if (actions[i] == WAKE_UP) {
			wake_up_minute = get_minute(dates[i]);
			for (int j = sleep_minute; j < wake_up_minute; ++j) {
				current->asleep[j]++;
				if (current->asleep[j] > current->max_minutes) {
					current->max_minutes = current->asleep[j];
					current->i_max_minutes = j;
				}
			}
		} else {
			if (first == NULL) {
				first = new_guard(actions[i]);
				current = first;
			} else {
				current = first;
				while (current->next != NULL) {
					if (current->id == actions[i])
						break;
					current = current->next;
				}
				if (current->id != actions[i]) {
					current->next = new_guard(actions[i]);
					current = current->next;
				}
			}
		}
	}

	Guard *max = first;
	current = first->next;
	while (current != NULL) {
		if (current->max_minutes > max->max_minutes)
			max = current;
		current = current->next;
	}

	int result = max->id * max->i_max_minutes;
	printf("Result: %d\n", result);

	return 0;
}