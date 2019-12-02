#include <iostream>
#include <vector>

int main() {
	std::vector<int> program;
	for (int n; std::cin >> n;) {
		program.push_back(n);
		std::cin.ignore(); // Ignore comma
	}

	program[1] = 12;
	program[2] = 2;

	int pc = 0; // Program counter
	bool running = true;
	while (running) {
		switch (program[pc]) {
		case 1: // Add
			program[program[pc+3]] = program[program[pc+1]] + program[program[pc+2]];
			break;
		case 2: // Multiply
			program[program[pc+3]] = program[program[pc+1]] * program[program[pc+2]];
			break;
		case 99: // Terminate
			running = false;
			break;
		default: // Error
			break;
		}
		pc += 4;
	}

	std::cout << program[0];

	return 0;
}
