#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

int main() {
	std::string line;
	std::cin >> line;

	int offset = std::stoi(line.substr(0, 7));
	if (2 * offset <= line.length() * 10000) {
		std::cout << "The solution won't work for this input" << std::endl;
		return 0;
	}

	int remaining = line.length() * 10000 - offset;
	std::vector<int> in(remaining);
	std::vector<int> out(remaining);
	for (int i = 0; i < in.size(); ++i) {
		in[i] = line[(i + offset) % line.length()] - '0';
	}

	for (int phase = 0; phase < 100; ++phase) {
		int sum = 0;
		for (int i = in.size() - 1; i >= 0; --i) {
			sum += in[i];
			out[i] = sum % 10;
		}
		in.swap(out);
	}

	for (int digit = 0; digit < 8; ++digit) {
		std::cout << in[digit];
	}
	std::cout << std::endl;

	return 0;
}
