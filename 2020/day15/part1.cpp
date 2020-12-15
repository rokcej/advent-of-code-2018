#include <iostream>
#include <string>
#include <vector>

int main() {
	std::vector<int> memory(2020, 0);
	int count = 0, prev;

	// Parse input
	std::string line;
	std::cin >> line;
	for (size_t pos = 0, end; pos < line.length(); pos = end + 1) {
		end = line.find(',', pos);
		if (end == std::string::npos)
			end = line.length();
		
		if (count > 0)
			memory[prev] = count; // One-indexed
		prev = std::stoi(line.substr(pos, end - pos));
		++count;
	}

	// Get result
	while (count != 2020) {
		int next = memory[prev] ? count - memory[prev] : 0;
		memory[prev] = count;
		prev = next;
		++count;
	}

	std::cout << prev << std::endl;

	return 0;
}
