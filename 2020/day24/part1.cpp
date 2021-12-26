#include <iostream>
#include <string>
#include <set>
#include <utility>

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

	std::cout << black.size() << std::endl;

	return 0;
}
