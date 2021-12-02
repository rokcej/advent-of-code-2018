#include <iostream>
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

	Intcode comp(program);
	std::vector<std::vector<char>> map;
	map.emplace_back(0);
	int row = 0, col = 0;

	while (true) {
		std::vector<ll> inputs = {};
		char c = (char)comp.execute(inputs);

		if (!comp.running)
			break;

		//std::cout << c;

		if (c == '\n') {
			if (map[row].size() > 0) {
				map.emplace_back(0);
				++row;
			}
		} else if (c == '.' || c == 'X') {
			map[row].push_back('.');
			if (row == 0)
				++col;
		} else {
			map[row].push_back('#');
			if (row == 0)
				++col;
		}
	}

	int sum = 0;

	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			if (map[i][j] == '#') {
				int neighbours = 0;
				if (i > 0 && map[i-1][j] == '#')
					++neighbours;
				if (i < row - 1 && map[i+1][j] == '#')
					++neighbours;
				if (j > 0 && map[i][j-1] == '#')
					++neighbours;
				if (j < col - 1 && map[i][j+1] == '#')
					++neighbours;
				
				if (neighbours >= 3) {
					map[i][j] = 'O';
					sum += i * j;
				}
			}
			//std::cout << (char)map[i][j];
		}
		//std::cout << std::endl;
	}

	std::cout << sum << std::endl;

	return 0;
}
