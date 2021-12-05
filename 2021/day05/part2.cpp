#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <utility>
#include <algorithm>
#include <chrono>

#define HASH(x,y) ((y << 16) | x) // Magic

int solve() {
	std::ifstream in("input");

	std::unordered_map<int, int> map;

	std::string line;
	while (in >> line) {
		int split = line.find(",");
		int x1 = std::stoi(line);
		int y1 = std::stoi(&line[split+1]);

		in >> line >> line;
		split = line.find(",");
		int x2 = std::stoi(line);
		int y2 = std::stoi(&line[split+1]);

		if (x1 == x2) {
			for (int y = std::min(y1,y2); y <= std::max(y1,y2); ++y) {
				++map[HASH(x1, y)];
			}
		} else if (y1 == y2) {
			for (int x = std::min(x1,x2); x <= std::max(x1,x2); ++x) {
				++map[HASH(x, y1)];
			}
		} else {
			int dx = x2 > x1 ? 1 : -1;
			int dy = y2 > y1 ? 1 : -1;
			for (int i = 0; i <= std::abs(x2 - x1); ++i) {
				++map[HASH(x1 + i*dx, y1 + i*dy)];
			}
		}
	}
	in.close();

	int result = 0;
	for (auto it = map.begin(); it != map.end(); ++it) {
		if (it->second >= 2) {
			++result;
		}
	}

	return result;
}

int main() {
	auto time_start = std::chrono::steady_clock::now();
	
	std::cout << solve() << std::endl;

	auto time_end = std::chrono::steady_clock::now();
	double time = std::chrono::duration<double>(time_end - time_start).count();
	std::cout << time << std::endl;
}
