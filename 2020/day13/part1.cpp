#include <iostream>
#include <string>
#include <vector>

int main() {
	std::vector<int> ids;

	// Read input
	int time;
	std::string line;
	std::cin >> time >> line;

	// Parse input
	for (size_t pos = 0, next; pos < line.length(); pos = next + 1) {
		next = line.find(',', pos);
		if (next == std::string::npos)
			next = line.length();
		if (line[pos] != 'x')
			ids.push_back(std::stol(line.substr(pos, next - pos)));
	}

	// Calculate result
	int result = ids[0];
	int min = result;
	for (int i = 1; i < ids.size(); ++i) {
		int r = ids[i] - (time % ids[i]);
		if (r < min) {
			min = r;
			result = ids[i];
		}
	}

	std::cout << result * min << std::endl;

	return 0;
}
