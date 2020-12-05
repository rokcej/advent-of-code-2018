#include <iostream>
#include <string>

int main() {
	int max = 0;

	std::string seat;
	while (std::cin >> seat) {
		int row = 0, col = 0;
		for (int i = 0; i < 7; ++i) {
			if (seat[6 - i] == 'B') row |= 1 << i;
		}
		for (int i = 0; i < 3; ++i) {
			if (seat[9 - i] == 'R')	col |= 1 << i;
		}
		int id = row * 8 + col;
		if (id > max) max = id;
	}

	std::cout << max << std::endl;

	return 0;
}
