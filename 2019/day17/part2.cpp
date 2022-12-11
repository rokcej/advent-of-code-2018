#include <iostream>
#include <vector>
#include <unordered_map>
#include <utility>

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
		std::vector<ll> inputs;
		ll input_counter = 0; // Input counter

		Intcode(Prog& program) {
			this->program = program;
		}

		ll execute() {
			ll input_counter2 = 0; // Input counter
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

bool can_visit(int x, int y, const std::vector<std::vector<char>>& map) {
	return x >= 0 && x < map[0].size() && y >= 0 && y < map.size() && map[y][x] == '#';
}

int main() {
	Prog program;
	int idx = 0;
	for (ll n; std::cin >> n;) {
		program[idx++] = n;
		std::cin.ignore(); // Ignore comma
	}

	// Generate map
	std::vector<std::vector<char>> map;
	map.emplace_back(0);
	int row = 0, col = 0;
	int x0, y0;

	for (Intcode comp(program); comp.running;) {
		char c = (char)comp.execute();

		if (c == '\n') {
			if (map[row].size() > 0) {
				map.emplace_back();
				++row;
			}
		} else {
			if (c == '^' || c == 'v' || c == '<' || c == '>') {
				x0 = col;
				y0 = row;
			}
			map[row].push_back(c);
			if (row == 0) {
				++col;
			}
		}
	}
	map.pop_back(); // Last line is empty

	int w = map[0].size();
	int h = map.size();

	// Rotate bot
	std::string commands;
	std::unordered_map<char, int> char2idx = {{'^', 0}, {'>', 1}, {'v', 2}, {'<', 3}};

	int dir = -1;
	int dirs[4][2] = { {0, -1}, {+1, 0}, {0, +1}, {-1, 0} }; // N, E, S, W
	for (dir = 0; dir < 4; ++dir) {
		int x2 = x0 + dirs[dir][0];
		int y2 = y0 + dirs[dir][1];
		if (can_visit(x2, y2, map)) {
			int dir0 = char2idx[map[y0][x0]];
			if ((dir0 + 1) % 4 == dir) {
				commands.push_back('R');
			} else if ((dir0 + 2) % 4 == dir) {
				commands.push_back('R');
				commands.push_back('R');
			} else if ((dir0 + 3) % 4 == dir) {
				commands.push_back('L');
			}
			break;
		}
	}

	// Visit every part of the scaffold
	for (int x = x0, y = y0, dist = 0;;) {
		// Forward
		int x2 = x + dirs[dir][0];
		int y2 = y + dirs[dir][1];
		if (can_visit(x2, y2, map)) {
			x = x2;
			y = y2;
			++dist;
			continue;
		}

		commands.push_back('0' + dist);
		dist = 0;

		// Left
		int dir2 = (dir + 3) % 4;
		x2 = x + dirs[dir2][0];
		y2 = y + dirs[dir2][1];
		if (can_visit(x2, y2, map)) {
			commands.push_back('L');
			dir = dir2;
			continue;
		}

		// Right
		dir2 = (dir + 1) % 4;
		x2 = x + dirs[dir2][0];
		y2 = y + dirs[dir2][1];
		if (can_visit(x2, y2, map)) {
			commands.push_back('R');
			dir = dir2;
			continue;
		}

		// Done
		break;
	}

	// Split commands into subroutines
	std::string main, A, B, C;
	for (int a = 10; a >= 1; --a) {
		A = commands.substr(0, a);
		int ib = a;
		while (ib + a < commands.length() && commands.substr(ib, a) == A) {
			ib += a;
		}
		for (int b = 10; b >= 1; --b) {
			if (ib + b > commands.length()) {
				continue;
			}
			B = commands.substr(ib, b);
			int ic = ib + b;
			for (int ic_prev = -1; ic != ic_prev;) {
				ic_prev = ic;
				if (ic + a < commands.length() && commands.substr(ic, a) == A) {
					ic += a;
				} else if (ic + b < commands.length() && commands.substr(ic, b) == B) {
					ic += b;
				}
			}
			for (int c = 10; c >= 1; --c) {
				if (ic + c > commands.length()) {
					continue;
				}
				C = commands.substr(ic, c);

				int i = a;
				main.push_back('A');

				for (int i_prev = -1; i != i_prev;) {
					i_prev = i;
					if (i + a <= commands.length() && commands.substr(i, a) == A) {
						i += a;
						main.push_back('A');
					} else if (i + b <= commands.length() && commands.substr(i, b) == B) {
						i += b;
						main.push_back('B');
					} else if (i + c <= commands.length() && commands.substr(i, c) == C) {
						i += c;
						main.push_back('C');
					}
				}
				if (i == commands.length()) {
					break;
				}
				main.clear();
			}
			if (main.length() > 0) {
				break;
			}
		}
		if (main.length() > 0) {
			break;
		}
	}

	// Convert subroutines into valid inputs
	std::vector<ll> main_input, A_input, B_input, C_input, video_input = {'n', '\n'};
	std::pair<std::string&, std::vector<ll>&> str2vec[] = { {main, main_input}, {A, A_input}, {B, B_input}, {C, C_input} };
	for (auto pair : str2vec) {
		for (char c : pair.first) {
			if (c > '9' && c < 'A') { // Works for up to 17, but it should be fine
				pair.second.push_back((c - '0') / 10 + '0');
				pair.second.push_back((c - '0') % 10 + '0');
			} else {
				pair.second.push_back(c);
			}
			pair.second.push_back(',');
		}
		pair.second[pair.second.size()-1] = '\n';
	}

	// for (auto x : main_input) std::cout << (char)x;
	// for (auto x : A_input) std::cout << (char)x;
	// for (auto x : B_input) std::cout << (char)x;
	// for (auto x : C_input) std::cout << (char)x;

	// Control robot
	program[0] = 2LL;
	Intcode comp(program);

	comp.inputs.insert(comp.inputs.end(), main_input.begin(), main_input.end());
	comp.inputs.insert(comp.inputs.end(), A_input.begin(), A_input.end());
	comp.inputs.insert(comp.inputs.end(), B_input.begin(), B_input.end());
	comp.inputs.insert(comp.inputs.end(), C_input.begin(), C_input.end());
	comp.inputs.insert(comp.inputs.end(), video_input.begin(), video_input.end());

	while (comp.running) {
		/*std::cout <<*/ (char)comp.execute();
	}
	std::cout << comp.execute() << std::endl;

	return 0;
}
