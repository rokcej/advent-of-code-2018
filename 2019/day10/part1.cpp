#include <iostream>
#include <string>
#include <vector>

typedef std::vector<std::string> Map;

int gcd(int a, int b) {
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

int main() {
	Map map;
	for (std::string line; std::getline(std::cin, line);) {
		if (line.length() > 0)
			map.push_back(line);
	}

	int h = map.size();
	int w = map[0].length();

	int maxCount = -1;
	int xMax = -1, yMax = -1;

	for (int y = 0; y < h; ++y) {
	for (int x = 0; x < w; ++x) {
		if (map[y][x] != '#')
			continue;

		int count = 0;
		for (int dy = -y; dy < h - y; ++dy) {
		for (int dx = -x; dx < w - x; ++dx) {
			int div = gcd(dx, dy);
			if (div > 1 || div < -1 || (dx == 0 && dy == 0))
				continue;

			int x2 = x + dx;
			int y2 = y + dy;
			while (x2 >= 0 && x2 < w && y2 >= 0 && y2 < h) {
				if (map[y2][x2] == '#') {
					++count;
					break;
				}
				x2 += dx;
				y2 += dy;
			}
		}
		}
		if (count > maxCount) {
			maxCount = count;
			xMax = x;
			yMax = y;
		}
	}
	}

	std::cout << maxCount << std::endl;
	
	return 0;
}
