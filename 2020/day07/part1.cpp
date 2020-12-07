#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>

std::string my_bag = "shiny gold";
std::unordered_map<std::string, std::unordered_set<std::string>> bags;

bool isValid(std::string bag, std::string first_bag) {
	for (auto subbag : bags[bag]) {
		if (subbag.compare(my_bag) == 0)
			return true;
		// Check for loops before making recursive calls
		if (subbag.compare(first_bag) != 0 && isValid(subbag, first_bag))
			return true;
	}

	return false;
}

int main() {
	// Parse input
	std::string shade, color, token, num;
	while (std::cin >> shade >> color >> token >> token >> num) {
		std::string bag = shade + " " + color;
		bags[bag] = std::unordered_set<std::string>();

		if (num.compare("no") == 0) {
			std::cin >> token >> token;
		} else {
			while (std::cin >> shade >> color >> token) {
				std::string subbag = shade + " " + color;
				bags[bag].insert(subbag);

				if (token.back() == '.')
					break;

				std::cin >> num;
			}
		}
	}

	// Compute result
	int result = 0;

	for (auto it : bags) {
		std::string bag = it.first;
		if (isValid(bag, bag))
			++result;
	}

	std::cout << result << std::endl;

	return 0;
}
