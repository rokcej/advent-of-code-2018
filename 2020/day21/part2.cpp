#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

int main() {
	std::unordered_map<std::string, std::unordered_set<std::string>> food;
	std::vector<std::string> list;

	std::vector<std::string> ingredients;
	for (std::string token; std::cin >> token;) {
		if (token.front() != '(') {
			ingredients.push_back(token);
			list.push_back(token);
		} else {
			std::vector<std::string> allergens;
			while (std::cin >> token) {
				allergens.push_back(token.substr(0, token.length() - 1));
				if (token.back() == ')') {
					for (std::string all : allergens) {
						if (food.find(all) == food.end()) {
							for (std::string ing : ingredients)
								food[all].insert(ing);
						} else {
							std::unordered_set<std::string> temp;
							for (std::string ing : ingredients) {
								if (food[all].find(ing) != food[all].end())
									temp.insert(ing);
							}
							food[all].swap(temp);
						}
					}
					ingredients.clear();
					allergens.clear();
					break;
				}
			}
		}
	}

	std::unordered_map<std::string, bool> final;
	bool changed;
	do {
		changed = false;
		for (auto f : food) {
			if (f.second.size() == 1 && !final[f.first]) {
				for (auto f2 : food) {
					if (f2.second.size() > 0 && f.first.compare(f2.first) != 0) {
						food[f2.first].erase(*(f.second.begin()));
					}
				}
				final[f.first] = true;
				changed = true;
			}
		}
	} while (changed);


	std::vector<std::string> sorted;
	for (auto f : food) {
		sorted.push_back(f.first);
	}
	std::sort(sorted.begin(), sorted.end());

	std::string result = "";
	bool first = true;
	for (auto s : sorted) {
		if (first)
			first = false;
		else
			result += ",";
		result += *(food[s].begin());
	}

	std::cout << result << std::endl;

	return 0;
}
