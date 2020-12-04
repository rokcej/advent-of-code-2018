#include <iostream>
#include <string>
#include <sstream>
#include <array>
#include <unordered_set>

int main() {
	std::unordered_set<std::string> required({"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"});

	int n_valid = 0;
	std::unordered_set<std::string> included;

	std::string line;
	while (std::getline(std::cin, line)) {
		if (line.empty()) {
			if (required.size() == included.size())
				++n_valid;
			included.clear();
		} else {
			std::istringstream iss(line);
			std::string token;
			while (iss >> token) {
				std::string key = token.substr(0, token.find(':'));
				if (required.find(key) != required.end())
					included.insert(key);
			}
		}
	}
	if (required.size() == included.size())
		++n_valid;
	included.clear();

	std::cout << n_valid << std::endl;

	return 0;
}
