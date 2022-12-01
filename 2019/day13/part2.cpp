#include <iostream>
#include <string>
#include <map>
#include <utility>
#include <vector>
#include <unordered_map>

typedef long long ll;
typedef std::unordered_map<ll, ll> Prog;

int digit(int val, int n) {
	int div = 1;
	for (int i = 0; i < n; ++i)
		div *= 10;
	return (val / div) % 10;
}

void get_params(std::vector<ll>& params, int num_params, int write_param, Prog& program, ll pc, ll rb) {
	ll modes = program[pc] / 100;
	for (int i = 0; i < num_params; ++i) {
		ll param = program[pc+i+1];
		ll mode = digit(modes, i);
		ll val;
		if (i == write_param) {
			val = param;
			if (mode == 2)
				val += rb;
		} else {
			if (mode == 0) // Position mode
				val = program[param];
			else if (mode == 1) // Immediate mode
				val = param;
			else // Relative mode
				val = program[param + rb];
		}
		params.push_back(val);
	}
}

class Intcode {
	private:
		Prog program;
		ll pc = 0; // Program counter
		ll rb = 0; // Relative base
		ll output = 0;
	public:
		bool running = true;

		Intcode(Prog& program) {
			this->program = program;
		}

		ll execute(std::vector<ll>& inputs) {
			ll input_counter = 0; // Input counter
			while (running) {
				ll opcode = program[pc] % 100;
				std::vector<ll> params;
				switch (opcode) {
					case 1: // Add
						get_params(params, 3, 2, program, pc, rb);
						program[params[2]] = params[0] + params[1];
						pc += 4;
						break;
					case 2: // Multiply
						get_params(params, 3, 2, program, pc, rb);
						program[params[2]] = params[0] * params[1];
						pc += 4;
						break;
					case 3: // Input
						get_params(params, 1, 0, program, pc, rb);
						program[params[0]] = inputs[input_counter++];
						pc += 2;
						break;
					case 4: // Output
						get_params(params, 1, -1, program, pc, rb);
						output = params[0];
						pc += 2;
						return output;
						break;
					case 5: // Jump-if-true
						get_params(params, 2, -1, program, pc, rb);
						if (params[0] != 0)
							pc = params[1];
						else
							pc += 3;
						break;
					case 6: // Jump-if-false
						get_params(params, 2, -1, program, pc, rb);
						if (params[0] == 0)
							pc = params[1];
						else
							pc += 3;
						break;
					case 7: // Less than
						get_params(params, 3, 2, program, pc, rb);
						if (params[0] < params[1])
							program[params[2]] = 1;
						else
							program[params[2]] = 0;
						pc += 4;
						break;
					case 8: // Equals
						get_params(params, 3, 2, program, pc, rb);
						if (params[0] == params[1])
							program[params[2]] = 1;
						else
							program[params[2]] = 0;
						pc += 4;
						break;
					case 9: // Relative base
						get_params(params, 1, -1, program, pc, rb);
						rb += params[0];
						pc += 2;
						break;
					case 99: // Terminate
						running = false;
						//pc += 1;
						break;
				}
			}
			return output;
		}
};

int main() {
	Prog program;
	int idx = 0;
	for (ll n; std::cin >> n;) {
		program[idx++] = n;
		std::cin.ignore(); // Ignore comma
	}

	program[0] = 2LL;

	int score = 0;
	int ball_x = 0;
	int board_x = 0;
	int input = 0;

	Intcode comp(program);
	while (comp.running) {
		std::vector<ll> inputs = { ball_x - board_x };

		int x = comp.execute(inputs);
		int y = comp.execute(inputs);
		int type = comp.execute(inputs);

		if (x == -1 && y == 0) {
			score = type;
			continue;
		}

		if (type == 3) {
			board_x = x;
		} else if (type == 4) {
			ball_x = x;
		}
	}

	std::cout << score << std::endl;

	return 0;
}
