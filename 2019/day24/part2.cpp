#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <unordered_map>

typedef std::vector<std::vector<bool>> Grid;
typedef std::unordered_map<int, Grid> GridMap;

void Update(int x, int y, int level, int max_level, const GridMap& read, GridMap& write) {
	// Ignore center
	if (x == 2 && y == 2) {
		return;
	}

	// Count neighbors
	int count = 0;
	std::pair<int, int> neighbors[4] = {{x-1, y}, {x+1, y}, {x, y-1}, {x, y+1}};
	for (auto [x2, y2] : neighbors) {
		int level2 = level;
		if (x2 == 2 && y2 == 2) {
			// Higher recursion level
			level2 = level + 1;
			if (level2 >= -max_level && level2 <= max_level) {
				if (x == x2) {
					for (int x3 = 0; x3 < 5; ++x3) {
						count += (int)read.at(level2)[y + (y - y2)][x3];
					}
				} else { // y == y2
					for (int y3 = 0; y3 < 5; ++y3) {
						count += (int)read.at(level2)[y3][x + (x - x2)];
					}
				}
			}
			continue;
		} else if (x2 < 0 || x2 >= 5 || y2 < 0 || y2 >= 5) {
			// Lower recursion level
			level2 = level - 1;
			x2 = 2 + (x2 - x);
			y2 = 2 + (y2 - y);
		}

		if (level2 >= -max_level && level2 <= max_level) {
			count += (int)read.at(level2)[y2][x2];
		}
	}
	
	// Update cell
	if (read.at(level)[y][x] && count != 1) {
		write.at(level)[y][x] = 0;
	} else if (!read.at(level)[y][x] && count >= 1 && count <= 2) {
		write.at(level)[y][x] = 1;
	} else {
		write.at(level)[y][x] = read.at(level)[y][x];
	}
}

int main() {
	std::vector<std::string> lines;
	for (std::string line; std::getline(std::cin, line);) {
		lines.push_back(line);
	}

	const int num_minutes = 200;
	int max_level = (num_minutes + 1) / 2;

	// Init all levels
	GridMap read, write;
	for (int level = -max_level; level <= max_level; ++level) {
		read.emplace(level, Grid(5, std::vector<bool>(5, false)));
		write.emplace(level, Grid(5, std::vector<bool>(5, false)));
	}
	for (int y = 0; y < 5; ++y) {
		for (int x = 0; x < 5; ++x) {
			read[0][y][x] = (bool)(lines[y][x] == '#');
		}
	}
	read[0][2][2] = false; // Ignore center

	// Simulate evolution
	for (int minute = 0; minute < num_minutes; ++minute) {
		for (int level = -max_level; level <= max_level; ++level) {
			for (int y = 0; y < 5; ++y) {
				for (int x = 0; x < 5; ++x) {
					Update(x, y, level, max_level, read, write);
				}
			}
		}
		read.swap(write);
	}

	// Count bugs
	int num_bugs = 0;
	for (int level = -max_level; level <= max_level; ++level) {
		for (int y = 0; y < 5; ++y) {
			for (int x = 0; x < 5; ++x) {
				num_bugs += (int)read[level][y][x];
			}
		}
	}
	std::cout << num_bugs << std::endl;

	return 0;
}
