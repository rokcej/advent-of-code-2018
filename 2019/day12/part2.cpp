#include <iostream>
#include <string>
#include <vector>

class Moon {
public:
	Moon(int x, int y, int z) : position{x, y, z}, velocity{0, 0, 0} {}

	int position[3];
	int velocity[3];
};

long long gcd(long long a, long long b) { // Greatest common divisor
	if (b == 0LL) {
		return a;
	}
	return gcd(b, a % b);
}

long long lcm(long long a, long long b) { // Least common multiple
	return a / gcd(a, b) * b;
}

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
	
	std::vector<Moon> moons_init(moons);

	long long periods[3] = {0LL, 0LL, 0LL};
	for (int dim = 0; dim < 3; ++dim) {
		while (true) {
			for (int i = 0; i < moons.size(); ++i) {
				for (int j = i + 1; j < moons.size(); ++j) {
					if (moons[i].position[dim] == moons[j].position[dim]) {
						continue;
					}
					int diff = moons[i].position[dim] < moons[j].position[dim] ? +1 : -1;
					moons[i].velocity[dim] += diff;
					moons[j].velocity[dim] -= diff;
				}
			}
			periods[dim]++;

			bool repeat = true;
			for (int i = 0; i < moons.size(); ++i) {
				moons[i].position[dim] += moons[i].velocity[dim];
				if (moons[i].position[dim] != moons_init[i].position[dim] || moons[i].velocity[dim] != moons_init[i].velocity[dim]) {
					repeat = false;
				}
			}
			if (repeat) {
				break;
			}
		}
	}

	std::cout << lcm(lcm(periods[0], periods[1]), periods[2]) << std::endl;

	return 0;
}
