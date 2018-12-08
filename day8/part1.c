#include <stdio.h>

int result = 0;

void rec() {
	int n_children, n_entries;
	scanf("%d %d", &n_children, &n_entries);
	for (int i = 0; i < n_children; ++i) {
		rec();
	}
	for (int i = 0; i < n_entries; ++i) {
		int entry;
		scanf("%d", &entry);
		result += entry;
	}
}

int main() {
	rec();
	printf("Result: %d\n", result);

	return 0;
}
