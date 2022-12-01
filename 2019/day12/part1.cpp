#include <iostream>
#include <string>
#include <vector>

class Moon {
public:
	Moon(int x, int y, int z) : position{x, y, z}, velocity{0, 0, 0} {}

	int position[3];
	int velocity[3];
};

int main() {
	std::vector<Moon> moons;
	
	for (std::string line; std::getline(std::cin, line); ) {
		int i0 = line.find(',');
		int i1 = line.find(',', i0 + 1);
		int i2 = line.find('>', i1 + 1);

		int x = std::stoi(line.substr(3, i0 - 3));
		int y = std::stoi(line.substr(i0 + 4, i1 - (i0 + 4)));
		int z = std::stoi(line.substr(i1 + 4, i2 - (i1 + 4)));

		moons.emplace_back(x, y, z);
	}

	for (int step = 0; step < 1000; ++step) {
		for (int i = 0; i < moons.size(); ++i) {
			for (int j = i + 1; j < moons.size(); ++j) {
				for (int k = 0; k < 3; ++k) {
					if (moons[i].position[k] == moons[j].position[k]) {
						continue;
					}
					int diff = moons[i].position[k] < moons[j].position[k] ? +1 : -1;
					moons[i].velocity[k] += diff;
					moons[j].velocity[k] -= diff;
				}
			}
		}

		for (int i = 0; i < moons.size(); ++i) {
			for (int k = 0; k < 3; ++k) {
				moons[i].position[k] += moons[i].velocity[k];
			}
		}
	}

	int energy = 0;
	for (int i = 0; i < moons.size(); ++i) {
		int pot = 0;
		int kin = 0;
		for (int k = 0; k < 3; ++k) {
			pot += std::abs(moons[i].position[k]);
			kin += std::abs(moons[i].velocity[k]);
		}
		energy += pot * kin;
	}
	std::cout << energy << std::endl;

	return 0;
}
