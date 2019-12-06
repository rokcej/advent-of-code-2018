#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

class Node {
	public:
		std::string id;
		std::vector<Node*> children;

		Node(std::string id) : id{id} {}
};

int orbits(Node *node, int depth) {
	int orbits_children = 0;
	for (int i = 0; i < node->children.size(); ++i)
		orbits_children += orbits(node->children[i], depth + 1);
	return depth + orbits_children;
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
	}

	Node *root = nodes["COM"];

	int result = orbits(root, 0);
	std::cout << result << std::endl;

	return 0;
}
