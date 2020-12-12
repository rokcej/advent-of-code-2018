#include <iostream>
#include <cmath>

int main() {
	const int dirs[8][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
	int dir = 0;
	int pos[2] = {0, 0};

	char act; int val;
	while (std::cin >> act >> val) {
		switch (act) {
			case 'N': pos[1] += val; break;
			case 'S': pos[1] -= val; break;
			case 'E': pos[0] += val; break;
			case 'W': pos[0] -= val; break;
			case 'L': dir = (dir +     val / 90) % 4; break;
			case 'R': dir = (dir + 4 - val / 90) % 4; break;
			case 'F':
				pos[0] += dirs[dir][0] * val;
				pos[1] += dirs[dir][1] * val;
				break;
		}
	}

	std::cout << std::abs(pos[0]) + std::abs(pos[1]) << std::endl;

	return 0;
}
