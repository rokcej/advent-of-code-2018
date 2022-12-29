#include <iostream>
#include <string>
#include <vector>

int shuffle(int position, const int count, const std::vector<std::string>& lines) {
	for (const std::string& line : lines) {
		if (line[0] == 'c') {
			// Cut
			int cut = std::stoi(line.substr(4));
			position = (position + count - cut) % count;
		} else if (line[5] == 'w') {
			// Deal with increment
			int increment = std::stoi(line.substr(20));
			position = (position * increment) % count;
		} else {
			// Deal into new stack
			position = (count - 1) - position;
		}
	}
	return position;
}

int main() {
	std::vector<std::string> lines;
	for (std::string line; std::getline(std::cin, line);) {
		lines.push_back(line);
	}

	const int count = 10007;
	const int position = 2019;

	std::cout << shuffle(position, count, lines) << std::endl;

	return 0;
}
