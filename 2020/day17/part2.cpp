#include <iostream>
#include <string>
#include <array>
#include <unordered_set>
#include <unordered_map>
#include <functional>

// 4D point object
struct Point {
	int x, y, z, w;
	Point(int x, int y, int z, int w) : x{x}, y{y}, z{z}, w{w} {}

	// Functions required for unordered_map and _set
	bool operator ==(const Point& p) const {
        return x == p.x && y == p.y && z == p.z && w == p.w;
    }
	struct Hash {
		size_t operator()(const Point& p) const { 
			// Encode coordinates into 32 bits and hash the result
			return std::hash<unsigned int>{}(
				(((p.w & 255) << 8 | (p.z & 255)) << 8 | (p.y & 255)) << 8 | (p.x & 255)
			);
		}
	};
};

int main() {
	// Read input
	std::unordered_set<Point, Point::Hash> alive;
	int col = 0;
	for (std::string line; std::cin >> line; ++col) {
		for (int row = 0; row < line.length(); ++row) {
			if (line[row] == '#')
				alive.insert(Point(row, col, 0, 0));
		}
	}

	// Generate list of offests for neighbors (permutations of -1, 0, 1)
	std::array<std::array<int, 4>, 3*3*3*3 - 1> offs;
	for (int n = 0, i = 0; n <= offs.size(); ++n) {
		int x = n%3 - 1, y = n/3%3 - 1, z = n/3/3%3 - 1, w = n/3/3/3%3 - 1;
		if (!(x == 0 && y == 0 && z == 0 && w == 0))
			offs[i++] = { x, y, z, w };
	}

	// Run simulation
	for (int step = 0; step < 6; ++step) {
		std::unordered_map<Point, int, Point::Hash> counts;
		std::unordered_set<Point, Point::Hash> temp;
		// Increment neighbors
		for (const Point& p : alive) {
			for (const auto& off : offs)
				counts[Point(p.x + off[0], p.y + off[1], p.z + off[2], p.w + off[3])] += 1;
		}
		// Determine living cells
		for (const auto& count : counts) {
			if (alive.find(count.first) == alive.end()) { // Dead
				if (count.second == 3)
					temp.insert(count.first);
			} else { // Alive
				if (count.second == 2 || count.second == 3)
					temp.insert(count.first);
			}
		}
		alive.swap(temp); // Update living cells
	}

	std::cout << alive.size() << std::endl;

	return 0;
}
