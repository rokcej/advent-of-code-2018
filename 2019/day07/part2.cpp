#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

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

int execute(std::vector<int>& program, std::vector<int>& inputs, int& output, int& pc) {
	int input_counter = 0; // Input counter
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
				program[program[pc+1]] = inputs[input_counter++];
				pc += 2;
				break;
			case 4: // Output
				get_params(params, 1, program, pc);
				output = params[0];
				pc += 2;
				return output;
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
				//pc += 1;
				break;
		}
	}
	return output;
}

int get_max_signal(std::vector<int> &settings, int depth, std::vector<int>& program) {
	if (depth < settings.size() - 1) { // Generate settings permutations
		int max_signal = std::numeric_limits<int>::min();
		for (int i = depth; i < settings.size(); ++i) {
			// Swap
			int temp = settings[depth];
			settings[depth] = settings[i];
			settings[i] = temp;

			max_signal = std::max(max_signal, get_max_signal(settings, depth+1, program));

			// Unswap
			settings[i] = settings[depth];
			settings[depth] = temp;
		}
		return max_signal;
	} else { // Calculate signal
		int n = settings.size();
		std::vector<std::vector<int>> amplifiers;
		std::vector<int> outputs;
		std::vector<int> pcs; // Program counters
		for (int i = 0; i < n; ++i) {
			amplifiers.push_back(program);
			outputs.push_back(0);
			pcs.push_back(0);
		}
		
		int signal = 0;
		bool first = true;
		while (amplifiers[n-1][pcs[n-1]] != 99) {
			for (int i = 0; i < n; ++i) {
				std::vector<int> inputs = { first ? settings[i] : signal };
				if (first) inputs.push_back(signal);
				signal = execute(amplifiers[i], inputs, outputs[i], pcs[i]);
			}
			first = false;
		}

		return signal;
	}
}

int main() {
	std::vector<int> program;
	for (int n; std::cin >> n;) {
		program.push_back(n);
		std::cin.ignore(); // Ignore comma
	}

	std::vector<int> settings = { 5, 6, 7, 8, 9 };
	int max_signal = get_max_signal(settings, 0, program);
	std::cout << max_signal << std::endl;

	return 0;
}
