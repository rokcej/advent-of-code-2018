#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

int main() {
	std::string line;
	std::cin >> line;

	std::vector<int> in(line.length());
	std::vector<int> out(line.length());
	for (int i = 0; i < line.length(); ++i) {
		in[i] = line[i] - '0';
	}

	int pattern[4] = { 0, 1, 0, -1 };
	for (int phase = 0; phase < 100; ++phase) {
		for (int i = 0; i < in.size(); ++i) {
			int sum = 0;
			for (int j = 0; j < in.size(); ++j) {
				sum += in[j] * pattern[((j + 1) / (i + 1)) % 4];
			}
			out[i] = std::abs(sum) % 10;
		}
		in.swap(out);
	}

	for (int digit = 0; digit < 8; ++digit) {
		std::cout << in[digit];
	}
	std::cout << std::endl;

	return 0;
}
