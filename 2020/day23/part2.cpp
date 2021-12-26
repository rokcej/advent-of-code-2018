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

	Node **nodes = new Node*[1000001];

	Node *curr = new Node(input[0] - '0');
	Node *last = curr;
	nodes[last->val] = last;
	for (int i = 1; i < input.size(); ++i) {
		last->next = new Node(input[i] - '0');
		last = last->next;
		nodes[last->val] = last;
	}
	for (int i = 10; i <= 1000000; ++i) {
		last->next = new Node(i);
		last = last->next;
		nodes[last->val] = last;
	}
	last->next = curr;

	for (int move = 0; move < 10000000; ++move) {
		// Lift 3 cups
		Node *lift0 = curr->next;
		Node *lift1 = lift0->next->next;
		curr->next = lift1->next;

		// Find destination
		int dest_val = curr->val-1 ? curr->val-1 : 1000000;
		while (dest_val == lift0->val || dest_val == lift0->next->val || dest_val == lift1->val) {
			dest_val = dest_val-1 ? dest_val-1 : 1000000;
		}
		Node *dest = nodes[dest_val];

		// Place 3 cups
		lift1->next = dest->next;
		dest->next = lift0;

		curr = curr->next;
	}

	long long result = (long long)nodes[1]->next->val * (long long)nodes[1]->next->next->val;
	std::cout << result << std::endl;

	return 0;
}
