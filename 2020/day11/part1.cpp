#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main() {
	std::vector<std::string> map;
	std::vector<std::string> temp;
	for (std::string line; std::cin >> line;) {
		map.push_back(line);
		temp.push_back(line);
	}

	bool changed;
	do {
		changed = false;
		for (int j = 0; j < map.size(); ++j) {
			int y0 = std::max(j - 1, 0), y1 = std::min(j + 1, (int)map.size() - 1);
			for (int i = 0; i < map[j].size(); ++i) {
				char seat = map[j][i];
				if (seat != '.') {
					int x0 = std::max(i - 1, 0), x1 = std::min(i + 1, (int)map[j].size() - 1);

					int adj = 0;
					for (int y = y0; y <= y1; ++y) {
					for (int x = x0; x <= x1; ++x) {
						if (!(x == i && y == j) && map[y][x] == '#')
							++adj;
					}
					}

					if (seat == 'L') {
						if (adj == 0) {
							seat = '#';
							changed = true;
						}
					} else if (seat == '#') {
						if (adj >= 4) {
							seat = 'L';
							changed = true;
						}
					}
					temp[j][i] = seat;
				}
			}
		}
		map.swap(temp);
	} while (changed);

	int result = 0;
	for (std::string row : map) {
		for (char seat : row) {
			if (seat == '#')
				++result;
		}
	}

	std::cout << result << std::endl;

	return 0;
}
