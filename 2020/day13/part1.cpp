#include <iostream>
#include <string>
#include <vector>

int main() {
	std::vector<int> ids;

	int time;
	std::string line;
	std::cin >> time >> line;

	for (size_t pos = 0, next; pos < line.length(); pos = next + 1) {
		next = line.find(',', pos);
		if (next == std::string::npos)
			next = line.length();
		if (line[pos] != 'x')
			ids.push_back(std::stol(line.substr(pos, next - pos)));
	}

	int result = ids[0];
	int min = result;
	for (auto id : ids) {
		int r = id - (time % id);
		if (r < min) {
			min = r;
			result = id;
		}
	}

	std::cout << result * min << std::endl;

	return 0;
}
