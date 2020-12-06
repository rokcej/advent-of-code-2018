#include <iostream>
#include <string>
#include <unordered_set>

int main() {
	std::unordered_set<char> everyone;
	bool first = true;
	int result = 0;
	
	std::string line;
	while (std::getline(std::cin, line)) {
		if (line.empty()) {
			result += everyone.size();
			everyone.clear();
			first = true;
		} else {
			if (first) {
				for (char c : line)
					everyone.insert(c);
				first = false;
			} else {
				std::unordered_set<char> temp;
				for (char c : line) {
					if (everyone.find(c) != everyone.end())
						temp.insert(c);
				}
				everyone.swap(temp);
			}
		}
	}
	result += everyone.size();

	std::cout << result << std::endl;

	return 0;
}
