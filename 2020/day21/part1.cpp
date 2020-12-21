#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

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

	int result = 0;
	for (auto s : list) {
		bool contains = false;
		for (auto f : food) {
			if (f.second.find(s) != f.second.end()) {
				contains = true;
				break;
			}
		}
		if (!contains)
			++result;
	}

	std::cout << result << std::endl;

	return 0;
}
