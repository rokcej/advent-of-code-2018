/**
 * Iteration min: -124339
 * Iteration max: 440
 * Iteration gain: 433
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct _Node {
	int value;
	struct _Node *next;
} Node;

Node *new_node(int value) {
	Node *node = malloc(sizeof(node));
	node->value = value;
	node->next = NULL;
	return node;
}

int main() {
	int *count = calloc((int) 4e5, sizeof(int));
	count += (int) 2e5;
	////////////////////

	int x;
	scanf("%d", &x);
	Node *firstInput = new_node(x);
	Node *lastInput = firstInput;
	// Read input into linked list
	while (scanf("%d", &x) != EOF) {
		lastInput->next = new_node(x);
		lastInput = lastInput->next;
	}
	// Make linked list into a loop
	lastInput->next = firstInput;
	Node *input = firstInput;
	// Endlessly loop input
	int sum = 0;

	while (1) {
		sum += input->value;
		if (count[sum]++ > 0)
			break;
		input = input->next;
	}

	////////////////////
	count -= (int) 2e5;
	free(count);

	printf("Result: %d\n", sum);
	return 0;
}
