#include <iostream>
#include <string>
#include <unordered_map>

std::string my_bag = "shiny gold";
std::unordered_map<std::string, std::unordered_map<std::string, int>> bags;

int countContents(std::string bag) {
	int count = 0;
	for (auto it : bags[bag]) {
		std::string subbag = it.first;
		int num = it.second;
		count += num * (1 + countContents(subbag));
	}
	return count;
}

int main() {
	// Parse input
	std::string shade, color, token, num;
	while (std::cin >> shade >> color >> token >> token >> num) {
		std::string bag = shade + " " + color;
		bags[bag] = std::unordered_map<std::string, int>();

		if (num.compare("no") == 0) {
			std::cin >> token >> token;
		} else {
			while (std::cin >> shade >> color >> token) {
				std::string subbag = shade + " " + color;
				bags[bag][subbag] = std::stoi(num);

				if (token.back() == '.')
					break;

				std::cin >> num;
			}
		}
	}

	// Compute result
	std::cout << countContents(my_bag) << std::endl;

	return 0;
}
