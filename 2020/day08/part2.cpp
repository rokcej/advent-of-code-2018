#include <iostream>
#include <vector>
#include <string>
#include <utility>

int accumulator = 0;

bool terminates(int pc, int* acc, int id, std::vector<std::pair<std::string, int>>& instructions, std::vector<int>& visited) {
	while (true) {
		if (pc == instructions.size())
			return true;
		if (visited[pc] == 1 || visited[pc] == id)
			return false;

		visited[pc] = id;

		std::string op = instructions[pc].first;
		int arg = instructions[pc].second;

		if (op.compare("acc") == 0) {
			*acc += arg;
			++pc;
		} else if (op.compare("jmp") == 0) {
			pc += arg;
		} else if (op.compare("nop") == 0) {
			++pc;
		}
	}
}

int main() {
	// Parse input
	std::vector<std::pair<std::string, int>> instructions;

	for (std::string op, arg; std::cin >> op >> arg;)
		instructions.push_back(std::make_pair(op, std::stoi(arg)));

	// Perform simulation
	int pc = 0; // Program counter
	int acc = 0;
	int id = 2; // Id for checking visited instructions
	std::vector<int> visited(instructions.size(), 0);

	while (visited[pc] != 1) {
		visited[pc] = 1;

		std::string op = instructions[pc].first;
		int arg = instructions[pc].second;

		if (op.compare("acc") == 0) {
			acc += arg;
			++pc;
		} else if (op.compare("jmp") == 0) {
			// Check if nop terminates
			int acc_ret = acc;
			if (terminates(pc + 1, &acc_ret, id++, instructions, visited)) {
				std::cout << acc_ret << std::endl;
				break;
			}
			// Execute jmp
			pc += arg;
		} else if (op.compare("nop") == 0) {
			// Check if jmp terminates
			int acc_ret = acc;
			if (terminates(pc + arg, &acc_ret, id++, instructions, visited)) {
				std:: cout << acc_ret << std::endl;
				break;
			}
			// Execute nop
			++pc;
		}
	}

	return 0;
}
