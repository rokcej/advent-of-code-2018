#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <utility>

int GetRating(const std::vector<std::vector<bool>>& map) {
	const int w = map[0].size();
	const int h = map.size();

	int rating = 0;
	int i = 0;
	for (int y = 0; y < h; ++y) {
		for (int x = 0; x < w; ++x) {
			if (map[y][x]) {
				rating |= (1 << i);
			}
			++i;
		}
	}
	return rating;
}

int main() {
	std::vector<std::vector<bool>> read, write;
	for (std::string line; std::getline(std::cin, line);) {
		read.emplace_back(line.length(), 0);
		write.emplace_back(line.length(), 0);
		for (int i = 0; i < line.length(); ++i) {
			read.back()[i] = (bool)(line[i] == '#');
		}
	}

	const int w = read[0].size();
	const int h = read.size();

	std::unordered_set<int> seen;
	seen.insert(GetRating(read));

	while (true) {
		for (int y = 0; y < h; ++y) {
			for (int x = 0; x < w; ++x) {
				int count = 0;
				std::pair<int, int> neighbors[4] = {{x-1, y}, {x+1, y}, {x, y-1}, {x, y+1}};
				for (const auto& [x2, y2] : neighbors) {
					if (x2 >= 0 && x2 < w && y2 >= 0 && y2 < h) {
						count += (int)read[y2][x2];
					}
				}
				if (read[y][x] && count != 1) {
					write[y][x] = 0;
				} else if (!read[y][x] && count >= 1 && count <= 2) {
					write[y][x] = 1;
				} else {
					write[y][x] = read[y][x];
				}
			}
		}
		read.swap(write);

		int rating = GetRating(read);
		if (seen.find(rating) != seen.end()) {
			std::cout << rating << std::endl;
			break;
		}
		seen.insert(rating);
	}

	return 0;
}
