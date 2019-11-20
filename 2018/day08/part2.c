#include <stdio.h>

int rec() {
	int value = 0;

	int n_children, n_entries;
	scanf("%d %d", &n_children, &n_entries);

	if (n_children == 0) {
		for (int i = 0; i < n_entries; ++i) {
			int entry;
			scanf("%d", &entry);
			value += entry;
		}
	} else {
		int children[n_children];
		for (int i = 0; i < n_children; ++i) {
			children[i] = rec();
		}
		for (int i = 0; i < n_entries; ++i) {
			int entry;
			scanf("%d", &entry);
			int idx = entry - 1;
			if (idx >= 0 && idx < n_children) {
				value += children[idx];
			}
		}
	}
	
	return value;
}

int main() {
	int result = rec();
	printf("Result: %d\n", result);

	return 0;
}
