#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <array>

int main() {
	std::vector<std::vector<std::array<int, 2>>> rules;

	// Read rules
	std::string line, token;
	while (std::getline(std::cin, line) && !line.empty()) {
		for (std::istringstream iss(line); iss >> token;) {
			if (token.back() == ':') {
				rules.emplace_back();
				std::string range[2];
				iss >> range[0] >> token >> range[1];
				for (int i = 0; i < 2; ++i) {
					int delim = range[i].find('-');
					int min = std::stoi(range[i].substr(0, delim));
					int max = std::stoi(range[i].substr(delim + 1));
					rules.back().push_back({min, max});
				}
			}
		}
	}

	// Skip my ticket
	while (std::getline(std::cin, line) && !line.empty());

	// Check nearby tickets
	int errorRate = 0;
	std::getline(std::cin, line);
	while (std::getline(std::cin, line) && !line.empty()) {
		for (std::istringstream iss(line); std::getline(iss, token, ',');) {
			int val = std::stoi(token);
			bool valid = false;
			for (auto field : rules) {
				for (auto range : field) {
					if (val >= range[0] && val <= range[1]) {
						valid = true;
						goto BREAK_OUTER_LOOP; // Last remaining use of goto in C++
					}
				}
			}
			BREAK_OUTER_LOOP:
			if (!valid)
				errorRate += val;
		}
	}
	
	std::cout << errorRate << std::endl;

	return 0;
}
