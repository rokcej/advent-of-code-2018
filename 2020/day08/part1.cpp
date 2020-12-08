#include <iostream>
#include <vector>
#include <string>
#include <utility>

int main() {
	// Parse input
	std::vector<std::pair<std::string, int>> instructions;

	for (std::string op, arg; std::cin >> op >> arg;)
		instructions.push_back(std::make_pair(op, std::stoi(arg)));

	// Perform simulation
	int pc = 0; // Program counter
	int acc = 0;
	std::vector<bool> visited(instructions.size(), false);

	while (!visited[pc]) {
		visited[pc] = true;

		std::string op = instructions[pc].first;
		int arg = instructions[pc].second;

		if (op.compare("acc") == 0) {
			acc += arg;
			++pc;
		} else if (op.compare("jmp") == 0) {
			pc += arg;
		} else if (op.compare("nop") == 0) {
			++pc;
		}
	}

	std::cout << acc << std::endl;

	return 0;
}
