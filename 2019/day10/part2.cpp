#include <iostream>
#include <string>
#include <vector>
#include <utility>

typedef std::vector<std::string> Map;
typedef std::pair<int, int> Dir;

const int MAX_REMOVED = 200;

int gcd(int a, int b) {
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

bool before(Dir a, Dir b) {
	if (a.first == 0) {
		if (-a.second > 0) return true;
		else return (b.first < 0);
	} else if (b.first == 0) {
		return !before(b, a);
	}

	if (a.first > 0 && b.first > 0 || a.first < 0 && b.first < 0) {
		float ka = -(float)a.second / (float)a.first;
		float kb = -(float)b.second / (float)b.first;
		return (ka > kb);
	} else if (a.first > 0 && b.first < 0) {
		return true;
	} else { //a.first < 0 && b.first > 0
		return false;
	}
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
	int xMax = -1;
	int yMax = -1;

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

	int x = xMax;
	int y = yMax;

	std::vector<Dir> dirs; // Directions
	for (int dy = -y; dy < h - y; ++dy) {
	for (int dx = -x; dx < w - x; ++dx) {
		int div = gcd(dx, dy);
		if (div > 1 || div < -1 || (dx == 0 && dy == 0))
			continue;

		int x2 = x + dx;
		int y2 = y + dy;
		while (x2 >= 0 && x2 < w && y2 >= 0 && y2 < h) {
			if (map[y2][x2] == '#') {
				Dir dir(dx, dy);
				auto iter = dirs.end();
				while (iter != dirs.begin() && before(dir, *(iter - 1)))
					--iter;
				dirs.insert(iter, dir);
				break;
			}
			x2 += dx;
			y2 += dy;
		}
	}
	}

	int removed = 0;
	int xRemoved = -1;
	int yRemoved = -1;
	while (removed != MAX_REMOVED) {
		for (int i = 0; i < dirs.size(); ++i) {
			int x2 = x + dirs[i].first;
			int y2 = y + dirs[i].second;
			while (x2 >= 0 && x2 < w && y2 >= 0 && y2 < h) {
				if (map[y2][x2] == '#') {
					map[y2][x2] = '.';
					++removed;
					xRemoved = x2;
					yRemoved = y2;
					break;
				}
				x2 += dirs[i].first;
				y2 += dirs[i].second;
			}
			if (removed == MAX_REMOVED)
				break;
		}
	}

	std::cout << 100 * xRemoved + yRemoved << std::endl;

	return 0;
}
