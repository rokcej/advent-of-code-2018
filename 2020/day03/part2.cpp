#include <iostream>
#include <string>

int main() {
	int slopes[5][2] = {{1, 1}, {3, 1}, {5, 1}, {7, 1}, {1, 2}};
	int trees[5] = {0, 0, 0, 0, 0};
	int y = 0;

	std::string line;
	while (std::cin >> line) {
		for (int i = 0; i < 5; ++i) {
			if (y % slopes[i][1] == 0) {
				int x = (y / slopes[i][1]) * slopes[i][0];
				if (line[x % line.length()] == '#')
					++trees[i];
			}
		}
		++y;
	}

	long long result = 1LL;
	for (int i = 0; i < 5; ++i)
		result *= trees[i];
	std::cout << result << std::endl;

	return 0;
}
