#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include <algorithm>
#include <cmath>

class Coord {
	public:
		int x, y;
		Coord(int x, int y) : x{x}, y{y} {};
};

void read_wire(std::vector<Coord>& wire) {
	std::string line;
	std::getline(std::cin, line);
	std::stringstream ss(line);
	for (std::string field; std::getline(ss, field, ',');) {
		char dir = field[0];
		int delta = std::stoi(field.substr(1));
		int dx = 0, dy = 0;
		switch (dir) {
			case 'R':
				dx = delta;
				break;
			case 'L':
				dx = -delta;
				break;
			case 'U':
				dy = delta;
				break;
			case 'D':
				dy = -delta;
				break;
			default: // Error
				break;
		}
		wire.push_back(Coord(dx, dy));
	}
}

void get_range(std::vector<Coord>& wire, Coord &min, Coord& max) {
	int x = 0, y = 0;
	for (auto coord : wire) {
		x += coord.x; y += coord.y;
		if (x > max.x) max.x = x;
		else if (x < min.x) min.x = x;
		if (y > max.y) max.y = y;
		else if (y < min.y) min.y = y;
	}
}

int main() {
	// Read input into vectors of coordinate pairs
	std::vector<Coord> wire1, wire2;
	read_wire(wire1);
	read_wire(wire2);

	// Get min and max coordinates
	Coord min(0, 0), max(0, 0);
	get_range(wire1, min, max);
	get_range(wire2, min, max);

	// Create 2D map and shift indexes
	char **map = new char*[max.y - min.y + 1];
	for (int i = 0; i < max.y - min.y + 1; ++i) {
		map[i] = new char[max.x - min.x + 1];
		for (int j = 0; j < max.x - min.x + 1; ++j)
			map[i][j] = 0;
		map[i] -= min.x;
	}
	map -= min.y;

	// Draw wire 1 on the map
	int x = 0, y = 0;
	for (auto coord : wire1) {
		if (coord.y == 0) {
			int sign = coord.x > 0 ? 1 : -1;
			for (int xi = x + sign; xi != x + coord.x + sign; xi += sign)
				map[y][xi] = 1;
		} else {
			int sign = coord.y > 0 ? 1 : -1;
			for (int yi = y + sign; yi != y + coord.y + sign; yi += sign)
				map[yi][x] = 1;
		}
		x += coord.x; y += coord.y;
	}

	// Find intersections of wire 2 with wire 1
	int dist = std::numeric_limits<int>::max();
	x = 0; y = 0;
	for (auto coord : wire2) {
		if (coord.y == 0) {
			int sign = coord.x > 0 ? 1 : -1;
			for (int xi = x + sign; xi != x + coord.x + sign; xi += sign) {
				if (map[y][xi] == 1)
					dist = std::min(dist, std::abs(y) + std::abs(xi));
			}
		} else {
			int sign = coord.y > 0 ? 1 : -1;
			for (int yi = y + sign; yi != y + coord.y + sign; yi += sign) {
				if (map[yi][x] == 1)
					dist = std::min(dist, std::abs(yi) + std::abs(x));
			}
		}
		x += coord.x; y += coord.y;
	}

	// Print result
	std::cout << dist << std::endl;

	return 0;
}
