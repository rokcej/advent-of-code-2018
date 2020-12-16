#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <array>
#include <unordered_set>

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

	// Read my ticket
	std::vector<int> ticket;
	std::getline(std::cin, line);
	std::getline(std::cin, line);
	for (std::istringstream iss(line); std::getline(iss, token, ',');)
		ticket.push_back(std::stoi(token));
	std::getline(std::cin, line); // Skip empty line

	// Create list of potential positions for each field
	std::vector<std::unordered_set<int>> positions;
	for (auto field : rules) {
		positions.emplace_back();
		for (int i = 0; i < rules.size(); ++i)
			positions.back().insert(i);
	}

	// Read and check nearby tickets
	std::getline(std::cin, line);
	while (std::getline(std::cin, line) && !line.empty()) {
		// Find valid tickets
		std::vector<std::unordered_set<int>> candidates;
		bool valid = true;
		for (std::istringstream iss(line); std::getline(iss, token, ',');) {
			candidates.emplace_back();
			int val = std::stoi(token);
			for (int i = 0; i < rules.size(); ++i) {
				for (auto range : rules[i]) {
					if (val >= range[0] && val <= range[1]) {
						candidates.back().insert(i);
						break;
					}
				}
			}
			if (candidates.back().empty()) {
				valid = false;
				break;
			}
		}
		// Use valid tickets to narrow down potential positions
		if (valid) {
			std::vector<std::unordered_set<int>> intersection(rules.size());
			for (int i = 0; i < rules.size(); ++i) {
				for (auto el : positions[i]) {
					if (candidates[i].find(el) != candidates[i].end())
						intersection[i].insert(el);
				}
			}
			positions.swap(intersection);
		}
	}

	// Reduce potential positions by elimination
	std::vector<bool> done(rules.size(), false);
	bool changed;
	do {
		changed = false;
		for (int i = 0; i < rules.size(); ++i) {
			if (!done[i] && positions[i].size() == 1) {
				int el = *(positions[i].begin());
				for (int j = 0; j < rules.size(); ++j) {
					if (j == i)
						continue;
					positions[j].erase(el);
				}
				done[i] = true;
				changed = true;
			}
		}
	} while (changed);

	// Get result
	long long result = 1LL;
	for (int i = 0; i < rules.size(); ++i) {
		int pos = *(positions[i].begin());
		if (pos < 6)
			result *= ticket[i];
	}

	std::cout << result << std::endl;
	
	return 0;
}
