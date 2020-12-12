#include <iostream>
#include <cmath>

int main() {
	int pos[2] = {0, 0};
	int way[2] = {10, 1};

	char act; int val;
	while (std::cin >> act >> val) {
		switch (act) {
			case 'N': way[1] += val; break;
			case 'S': way[1] -= val; break;
			case 'E': way[0] += val; break;
			case 'W': way[0] -= val; break;
			case 'L':
				for (int i = 0; i < val / 90; ++i) {
					int x = way[0];
					way[0] = -way[1];
					way[1] = x;
				}
				break;
			case 'R':
				for (int i = 0; i < val / 90; ++i) {
					int x = way[0];
					way[0] = way[1];
					way[1] = -x;
				}
				break;
			case 'F':
				pos[0] += way[0] * val;
				pos[1] += way[1] * val;
				break;
		}
	}

	std::cout << std::abs(pos[0]) + std::abs(pos[1]) << std::endl;

	return 0;
}
