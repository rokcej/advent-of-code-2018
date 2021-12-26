#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <utility>

std::vector<std::pair<int, int>> get_neighs(std::pair<int, int> pair) {
	int y = pair.first;
	int x = pair.second;
	int o = y % 2 != 0;
	return {
		{y, x+1}, {y-1, x+o}, {y-1, x-1+o}, {y, x-1}, {y+1, x-1+o}, {y+1, x+o}
	};
}

int main() {
	std::set<std::pair<int, int>> black;

	for (std::string line; std::cin >> line;) {
		int y = 0, x = 0;
		for (int i = 0; i < line.size(); ++i) {
			if (line[i] == 'e') {
				++x;
			} else if (line[i] == 'w') {
				--x;
			} else {
				if (y % 2 != 0) {
					++x;
				}

				std::string dir = line.substr(i++, 2);
				if (dir == "ne") {
					++y;
				} else if (dir == "nw") {
					++y; --x;
				} else if (dir == "se") {
					--y;
				} else { // sw
					--y; --x;
				}
			}
		}
		auto key = std::make_pair(y, x);
		if (black.find(key) == black.end()) {
			black.insert(key);
		} else {
			black.erase(key);
		}
	}
	
	for (int day = 0; day < 100; ++day) {
		std::set<std::pair<int, int>> to_remove;
		std::set<std::pair<int, int>> to_add;

		for (const auto &pair : black) {
			int black_count = 0;
			auto neighs = get_neighs(pair);
			for (const auto &neigh : neighs) {
				if (black.find(neigh) != black.end()) {
					++black_count;
				} else {
					int black_count2 = 0;
					auto neighs2 = get_neighs(neigh);
					for (const auto &neigh2 : neighs2) {
						if (black.find(neigh2) != black.end()) {
							++black_count2;
						}
					}
					if (black_count2 == 2) {
						to_add.insert(neigh);
					}
				}
			}
			if (black_count == 0 || black_count > 2) {
				to_remove.insert(pair);
			}
		}

		for (const auto &pair : to_remove) {
			black.erase(pair);
		}
		for (const auto &pair : to_add) {
			black.insert(pair);
		}
	}

	std::cout << black.size() << std::endl;

	return 0;
}
