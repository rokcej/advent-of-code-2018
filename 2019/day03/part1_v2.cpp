#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>

class Line {
	public:
		int x, y;
		int dx, dy;
		Line(int x, int y, int dx, int dy) : x{x}, y{y}, dx{dx}, dy{dy} {};
};

void read_wire(std::vector<Line>& wire) {
	std::string line;
	std::getline(std::cin, line);
	std::stringstream ss(line);
	int x = 0, y = 0;
	for (std::string field; std::getline(ss, field, ',');) {
		char dir = field[0];
		int delta = std::stoi(field.substr(1));
		int dx = 0, dy = 0;
		int x0 = x, y0 = y;
		switch (dir) {
			case 'R':
				dx = delta - 1;
				x0 = x + 1;
				x += delta;
				break;
			case 'L':
				dx = delta - 1;
				x0 = x - delta;
				x -= delta;
				break;
			case 'U':
				dy = delta - 1;
				y0 = y + 1;
				y += delta;
				break;
			case 'D':
				dy = delta - 1;
				y0 = y - delta;
				y -= delta;
				break;
		}
		wire.push_back(Line(x0, y0, dx, dy));
	}
}

int intersect_orthogonal(const Line& l1, const Line& l2) {
	if (
		l1.x >= l2.x && l1.x <= l2.x + l2.dx &&
		l2.y >= l1.y && l2.y <= l1.y + l1.dy 
	) {
		return std::abs(l1.x) + std::abs(l2.y);
	} else {
		return -1;
	}
}

int intersect_parallel(Line l1, Line l2) {
	if (l1.y >= l2.y && l1.y <= l2.y + l2.dy ||
		l2.y >= l1.y && l2.y <= l1.y + l1.dy
	) {
		int y0 = std::max(l1.y, l2.y);
		int y1 = std::min(l1.y + l1.dy, l2.y + l2.dy);
		int y;
		if (y0 > 0) y = y0;
		else if (y1 < 0) y = -y1;
		else y = 0;
		return std::abs(l1.x) + y;
	} else {
		return -1;
	}
}

int intersect(const Line& l1, const Line& l2) {
	if (l1.dx == 0 && l2.dy == 0) {
		return intersect_orthogonal(l1, l2);	
	} else if (l1.dy == 0 && l2.dx == 0) {
		return intersect_orthogonal(l2, l1);
	} else if (l1.dx == 0 && l1.x == l2.x) {
		return intersect_parallel(l1, l2);
	} else if (l1.dy == 0 && l1.y == l2.y) {
		return intersect_parallel(Line(l1.y, l1.x, l1.dy, l1.dx), Line(l2.y, l2.x, l2.dy, l2.dx));
	} else {
		return -1;
	}
}

int main() {
	// Read input into vectors of coordinate pairs
	std::vector<Line> wire1, wire2;
	read_wire(wire1);
	read_wire(wire2);

	// Check all line pairs for intersections
	int minDist = -1;
	for (auto& l1 : wire1) {
		for (auto& l2 : wire2) {
			int dist = intersect(l1, l2);
			if (dist != -1 && (minDist == -1 || dist < minDist))
				minDist = dist;
		}
	}

	std::cout << minDist << std::endl;

	return 0;
}
