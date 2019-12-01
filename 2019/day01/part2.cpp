#include <iostream>

int main() {
	int sum = 0;
	for (int mass; std::cin >> mass;) {
		int fuel = mass / 3 - 2;
		while (fuel > 0) {
			sum += fuel;
			fuel = fuel / 3 - 2;
		}
	}
	std::cout << sum << std::endl;

	return 0;
}
