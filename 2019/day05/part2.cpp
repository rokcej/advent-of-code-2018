#include <iostream>
#include <vector>

int digit(int val, int n) {
	int div = 1;
	for (int i = 0; i < n; ++i)
		div *= 10;
	return (val / div) % 10;
}

void get_params(std::vector<int>& params, int num_params, std::vector<int>& program, int pc) {
	int modes = program[pc] / 100;
	for (int i = 0; i < num_params; ++i) {
		int param = program[pc+i+1];
		int mode = digit(modes, i);
		int val;
		if (mode == 0) // Position mode
			val = program[param];
		else // Immediate mode
			val = param;
		params.push_back(val);
	}
}

int execute(std::vector<int>& program) {
	int output = 0;
	int pc = 0; // Program counter
	bool running = true;
	while (running) {
		int opcode = program[pc] % 100;
		std::vector<int> params;
		switch (opcode) {
			case 1: // Add
				get_params(params, 2, program, pc);
				program[program[pc+3]] = params[0] + params[1];
				pc += 4;
				break;
			case 2: // Multiply
				get_params(params, 3, program, pc);
				program[program[pc+3]] = params[0] * params[1];
				pc += 4;
				break;
			case 3: // Input
				program[program[pc+1]] = 5;
				pc += 2;
				break;
			case 4: // Output
				get_params(params, 1, program, pc);
				output = params[0];
				pc += 2;
				break;
			case 5: // Jump-if-true
				get_params(params, 2, program, pc);
				if (params[0] != 0)
					pc = params[1];
				else
					pc += 3;
				break;
			case 6: // Jump-if-false
				get_params(params, 2, program, pc);
				if (params[0] == 0)
					pc = params[1];
				else
					pc += 3;
				break;
			case 7: // Less than
				get_params(params, 2, program, pc);
				if (params[0] < params[1])
					program[program[pc+3]] = 1;
				else
					program[program[pc+3]] = 0;
				pc += 4;
				break;
			case 8: // Equals
				get_params(params, 2, program, pc);
				if (params[0] == params[1])
					program[program[pc+3]] = 1;
				else
					program[program[pc+3]] = 0;
				pc += 4;
				break;
			case 99: // Terminate
				running = false;
				pc += 1;
				break;
		}
	}
	return output;
}

int main() {
	std::vector<int> program;
	for (int n; std::cin >> n;) {
		program.push_back(n);
		std::cin.ignore(); // Ignore comma
	}

	int output = execute(program);
	std::cout << output << std::endl;

	return 0;
}
