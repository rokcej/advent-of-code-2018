#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_set>
#include <regex>

std::vector<std::vector<std::vector<int>>> rules;
std::vector<std::string> patterns;

void getPattern(int i) {
	for (auto rule : rules[i]) {
		for (int r : rule) {
			if (patterns[r].empty())
				getPattern(r);
		}
		std::string pattern(patterns[rule[0]]);
		for (int ir = 1; ir < rule.size(); ++ir) {
			pattern += patterns[rule[ir]];
		}
		if (patterns[i].empty())
			patterns[i] = pattern;
		else
			patterns[i] = "(" + patterns[i] + "|" + pattern + ")";
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
				patterns[id] = token.substr(1, token.length() - 2);
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
		if (std::regex_match(line, std::regex(patterns[0])))
		 	++result;
	}

	std::cout << result << std::endl;

	return 0;
}
