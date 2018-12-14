#include <stdio.h>
#include <stdlib.h>

int *recipes;
int len;
int lenMax;

void push(int item) {
	if (len >= lenMax) {
		lenMax <<= 1;
		recipes = realloc(recipes, lenMax * sizeof(int));
	}
	recipes[len++] = item;
}

int main() {
	int input;
	scanf("%d", &input);

	len = 0;
	lenMax = 1;
	while (lenMax < input + 10)
		lenMax <<= 1;

	recipes = malloc(lenMax * sizeof(int));
	push(3);
	push(7);

	int first = 0;
	int second = 1;

	int pattern[6];
	int temp = input;
	for (int i = 5; i >= 0; --i) {
		pattern[i] = temp % 10;
		temp /= 10;
	}

	int index = 0;
	while (1) {
		int sum = recipes[first] + recipes[second];
		if (sum < 10) {
			push(sum);
		} else {
			push(sum / 10);
			push(sum % 10);
		}

		while (index < len - 5) {
			int match = 1;
			for (int j = 0; j < 6; ++j) {
				if (recipes[index+j] != pattern[j]) {
					match = 0;
					break;
				}
			}
			if (match) {
				printf("Result: %d\n", index);
				return 0;
			}
			++index;
		}

		first = (first + recipes[first] + 1) % len;
		second = (second + recipes[second] + 1) % len;
	}

	return 0;
}
