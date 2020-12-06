#include <iostream>
#include <string>

int main() {
	int questions['z' - 'a' + 1] = { 0 };
	int result = 0;
	int group = 1;
	
	std::string line;
	while (std::getline(std::cin, line)) {
		if (line.empty()) {
			++group;
		} else {
			for (char c : line) {
				if (questions[c - 'a'] != group) {
					++result;
					questions[c - 'a'] = group;
				}
			}
		}
	}

	std::cout << result << std::endl;

	return 0;
}
