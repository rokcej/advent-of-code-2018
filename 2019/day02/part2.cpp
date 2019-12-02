#include <iostream>
#include <vector>

void execute(std::vector<int>& program) {
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
}

int main() {
	std::vector<int> program;
	for (int n; std::cin >> n;) {
		program.push_back(n);
		std::cin.ignore(); // Ignore comma
	}

	for (int noun = 0; noun <= 99; ++noun) {
		for (int verb = 0; verb <= 99; ++verb) {
			std::vector<int> program_copy = program;
			program_copy[1] = noun;
			program_copy[2] = verb;
			execute(program_copy);
			
			if (program_copy[0] == 19690720) {
				std::cout << 100 * noun + verb << std::endl;
				return 0;
			}
		}
	}

	return 0;
}
