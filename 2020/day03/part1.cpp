#include <iostream>
#include <string>

int main() {
	int x = 0;
	int trees = 0;

	std::string line;
	while (std::cin >> line) {
		if (line[x] == '#')
			++trees;
		x = (x + 3) % line.length();
	}

	std::cout << trees << std::endl;

	return 0;
}
