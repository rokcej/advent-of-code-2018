#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main() {
	const int dir[8][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {1, -1}, {-1, 1}, {1, 1}};
	
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
		for (int i = 0; i < map[j].size(); ++i) {
			char seat = map[j][i];
			if (seat != '.') {
				int adj = 0;
				for (int d = 0; d < 8; ++d) {
					int x = i + dir[d][0];
					int y = j + dir[d][1];
					while (x >= 0 && x < map[j].size() && y >= 0 && y < map.size()) {
						if (map[y][x] != '.') {
							if (map[y][x] == '#')
								++adj;
							break;
						}
						x += dir[d][0];
						y += dir[d][1];
					}
				}

				if (seat == 'L') {
					if (adj == 0) {
						seat = '#';
						changed = true;
					}
				} else if (seat == '#') {
					if (adj >= 5) {
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
