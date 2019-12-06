#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

class Node {
	public:
		std::string id;
		Node *parent = nullptr;
		std::vector<Node*> children;
		bool visited = false;

		Node(std::string id) : id{id} {}
};

// Uses DFS. BFS would be better but takes more time to implement
int transfers(Node *node, int distance, Node *goal) {
	if (node == nullptr || node->visited)
		return -1;
	node->visited = true;

	if (node == goal)
		return distance;

	int temp = transfers(node->parent, distance + 1, goal);
	if (temp >= 0)
		return temp;
	
	for (int i = 0; i < node->children.size(); ++i) {
		temp = transfers(node->children[i], distance + 1, goal);
		if (temp >= 0)
			return temp;
	}

	return -1;
}

int main() {
	std::unordered_map<std::string, Node*> nodes;
	for (std::string line; std::getline(std::cin, line);) {
		int idx = line.find(')');
		std::string parentId = line.substr(0, idx);
		std::string childId = line.substr(idx + 1);

		Node *parent, *child;
		auto iter = nodes.find(parentId);
		if (iter == nodes.end()) {
			parent = new Node(parentId);
			nodes[parentId] = parent;
		} else {
			parent = iter->second;
		}
		iter = nodes.find(childId);
		if (iter == nodes.end()) {
			child = new Node(childId);
			nodes[childId] = child;
		} else {
			child = iter->second;
		}

		parent->children.push_back(child);
		child->parent = parent;
	}

	int result = transfers(nodes["YOU"]->parent, 0, nodes["SAN"]->parent);
	std::cout << result << std::endl;

	return 0;
}
