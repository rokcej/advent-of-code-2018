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

	while (len < input + 10) {
		int sum = recipes[first] + recipes[second];
		if (sum < 10) {
			push(sum);
		} else {
			push(sum / 10);
			push(sum % 10);
		}

		first = (first + recipes[first] + 1) % len;
		second = (second + recipes[second] + 1) % len;		
	}

	
	printf("Result: ");
	for (int i = input; i < input + 10; ++i)
		printf("%c", '0' + recipes[i]);
	printf("\n");

	return 0;
}
