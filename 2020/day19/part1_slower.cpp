#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_set>

std::vector<std::vector<std::vector<int>>> rules;
std::vector<std::unordered_set<std::string>> patterns;

void getPattern(int i) {
	for (auto rule : rules[i]) {
		for (int r : rule) {
			if (patterns[r].empty())
				getPattern(r);
		}
		std::unordered_set<std::string> pattern(patterns[rule[0]]);
		for (int ir = 1; ir < rule.size(); ++ir) {
			std::unordered_set<std::string> temp;
			for (std::string p0 : pattern) {
				for (std::string p1 : patterns[rule[ir]]) {
					temp.insert(p0 + p1);
				}
			}
			pattern.swap(temp);
		}
		for (std::string p : pattern) {
			patterns[i].insert(p);
		}
	}
}

int main() {
	std::vector<std::string> lines;
	for (std::string line; std::getline(std::cin, line) && !line.empty();)
		lines.push_back(line);

	rules.resize(lines.size());
	patterns.resize(lines.size());

	for (std::string line : lines) {
		std::istringstream iss(line);
		std::string token;
		iss >> token;
		int id = std::stoi(token.substr(0, token.length() - 1));
		while (iss >> token) {
			if (token[0] == '"') {
				patterns[id].insert(token.substr(1, token.length() - 2));
			} else {
				int i = std::stoi(token);
				rules[id].emplace_back();
				rules[id].back().push_back(i);
				while (iss >> token && token[0] != '|') {
					int i = std::stoi(token);
					rules[id].back().push_back(i);
				}
			}
		}
	}

	if (patterns[0].empty())
		getPattern(0);

	int result = 0;
	for (std::string line; std::cin >> line;) {
		if (patterns[0].find(line) != patterns[0].end())
			++result;
	}

	std::cout << result << std::endl;

	return 0;
}
