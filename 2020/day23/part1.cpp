#include <iostream>
#include <string>

class Node {
public:
	int val;
	Node *next = nullptr;

	Node(int val) {
		this->val = val;
	}
};

int main() {
	std::string input;
	std::cin >> input;

	Node *curr = new Node(input[0] - '0');
	Node *last = curr;
	for (int i = 1; i < input.size(); ++i) {
		last->next = new Node(input[i] - '0');
		last = last->next;
	}
	last->next = curr;

	for (int move = 0; move < 100; ++move) {
		// Lift 3 cups
		Node *lift0 = curr->next;
		Node *lift1 = lift0->next->next;
		curr->next = lift1->next;

		// Find destination
		int dest_val = curr->val-1 ? curr->val-1 : 9;
		while (dest_val == lift0->val || dest_val == lift0->next->val || dest_val == lift1->val) {
			dest_val = dest_val-1 ? dest_val-1 : 9;
		}
		Node *dest = curr->next;
		while (dest->val != dest_val) {
			dest = dest->next;
		}

		// Place 3 cups
		lift1->next = dest->next;
		dest->next = lift0;

		curr = curr->next;
	}

	Node *one = curr;
	while (one->val != 1) {
		one = one->next;
	}
	int result = 0;
	for (Node *n = one->next; n != one; n = n->next) {
		result = result * 10 + n->val;
	}
	std::cout << result << std::endl;

	return 0;
}
