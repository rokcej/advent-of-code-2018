#include <iostream>

int main() {
	int sum = 0;
	for (int mass; std::cin >> mass;)
		sum += mass / 3 - 2;
	std::cout << sum << std::endl;

	return 0;
}
