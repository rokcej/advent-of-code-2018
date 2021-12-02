#include <iostream>
#include <vector>
#include <cstdlib>

class Moon {
	public:
		int pos[3];
		int vel[3] = {0, 0, 0};

		Moon(int x, int y, int z) : pos{x, y, z} {}
};

int main() {
	std::vector<Moon> moons;

	while (std::cin.peek() == '<') {
		int x, y, z;
		std::cin.ignore(256, '=');
		std::cin >> x;
		std::cin.ignore(256, '=');
		std::cin >> y;
		std::cin.ignore(256, '=');
		std::cin >> z;
		std::cin.ignore(256, '\n');

		moons.emplace_back(x, y, z);
	}

	for (int step = 0; step < 1000; ++step) {
		std::vector<std::vector<int>> gravities;
		for (int i = 0; i < moons.size(); ++i)
			gravities.emplace_back(3, 0);

		for (int i = 0; i < moons.size(); ++i) {
			for (int j = i + 1; j < moons.size(); ++j) {
				for (int k = 0; k < 3; ++k) {
					if (moons[i].pos[k] < moons[j].pos[k]) {
						++gravities[i][k];
						--gravities[j][k];
					} else if (moons[i].pos[k] > moons[j].pos[k]) {
						--gravities[i][k];
						++gravities[j][k];
					}
				}
			}
		}

		for (int i = 0; i < moons.size(); ++i) {
			for (int k = 0; k < 3; ++k) {
				moons[i].vel[k] += gravities[i][k];
				moons[i].pos[k] += moons[i].vel[k];
			}
		}
	}

	int energy = 0;
	for (int i = 0; i < moons.size(); ++i) {
		int pot = 0;
		int kin = 0;
		for (int k = 0; k < 3; ++k) {
			pot += std::abs(moons[i].pos[k]);
			kin += std::abs(moons[i].vel[k]);
		}
		energy += pot * kin;
	}
	std::cout << energy << std::endl;
	
	return 0;
}
