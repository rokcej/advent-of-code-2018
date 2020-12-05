#include <iostream>
#include <string>

int main() {
	int seats[1024] = { 0 };

	std::string seat;
	while (std::cin >> seat) {
		int row = 0, col = 0;
		for (int i = 0; i < 7; ++i) {
			if (seat[6 - i] == 'B')	row |= 1 << i;
		}
		for (int i = 0; i < 3; ++i) {
			if (seat[9 - i] == 'R')	col |= 1 << i;
		}
		int id = row * 8 + col;
		seats[id] = 1;
	}

	for (int i = 1; i < 1023; ++i) {
		if (!seats[i] && seats[i-1] && seats[i+1]) {
			std::cout << i << std::endl;
			break;
		}
	}

	return 0;
}
