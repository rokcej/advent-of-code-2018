#include <stdio.h>

int main() {
	int sum = 0;

	int x;
	while (scanf("%d", &x) != EOF) {
		sum += x;
	}

	printf("Result: %d\n", sum);

	return 0;
}
