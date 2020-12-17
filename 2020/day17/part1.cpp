#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <algorithm>

constexpr int STEPS = 6;
constexpr int X = 20, Y = 20, Z = 13; // initial_size + 2 * steps

// 3D memory indexing
inline int I(const int& x, const int& y, const int& z) {
	return (z * Y + y) * X + x;
}

int main() {
	// Read input
	std::vector<std::string> input;
	for (std::string line; std::cin >> line;)
		input.push_back(line);

	// Init 3D map
	std::vector<int> map(Z * Y * X, false);
	std::vector<int> tmp(Z * Y * X, false);
	for (int y = 0; y < input.size(); ++y) {
		for (int x = 0; x < input[0].length(); ++x) {
			if (input[y][x] == '#')
				map[I(x + STEPS, y + STEPS, STEPS)] = true;
		}
	}

	// Run simulation
	for (int step = 0; step < STEPS; ++step) {
		// Loop over all coordinates
		for (int z = 0; z < Z; ++z) {
			int z0 = std::max(z-1, 0), z1 = std::min(z+1, Z-1);
			for (int y = 0; y < Y; ++y) {
				int y0 = std::max(y-1, 0), y1 = std::min(y+1, Y-1);
				for (int x = 0; x < X; ++x) {
					int x0 = std::max(x-1, 0), x1 = std::min(x+1, X-1);
					// Loop over all neighbors
					int count = 0;
					for (int zn = z0; zn <= z1; ++zn) {
						for (int yn = y0; yn <= y1; ++yn) {
							for (int xn = x0; xn <= x1; ++xn) {
								if (xn == x && yn == y && zn == z)
									continue;
								if (map[I(xn, yn, zn)]) {
									if (++count > 3)
										goto BREAK_NEIGHBOR_LOOP; // Last remaining use of goto in C++
								}
							}
						}
					}
					BREAK_NEIGHBOR_LOOP:
					int i = I(x, y, z);
					tmp[i] = map[i] ? (count == 2 || count == 3) : (count == 3);
				}
			}
		}
		map.swap(tmp);
	}

	// Get result
	int result = 0;
	for (auto cube : map) {
		if (cube)
			++result;
	}

	std::cout << result << std::endl;

	return 0;
}
