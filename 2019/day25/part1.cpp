/*
+--------------------------------------+
| Map of Santa's ship                  |
| Do not pick up items marked with (X) |
+---=----------------------------------+
                                                        Passages
                                                        -mutex
                                                            |
                                                        Observatory             Holodeck
                                                            |                   -loom
                                                            |                      |
Science lab ------- Security checkpoint --- Santa      Gift wrapping center --- Corridor            Hot chocolate fountain -------- Storage --------------- Navigation
-dark matter            |                                   |                   -escape pod (X)     -giant electromagnet (X)        -infinite loop (X)      -photons (X)
    |                   |                                   |                                                                                                   |
    |                   |                                   |                                                                                                   |
Hallway ----------- Engineering ----------------------- Hull breach------------ Kitchen-------------------------------------------------------------------- Arcade
-sand                   |                                                       -semiconductor                                                              -ornament
    |                   |
    |               Crew quarters
    |
    |
    |               Stables
    |               -wreath
    |                   |
Sick bay ---------- Warp drive maintenance
-molten lava (X)    -asterisk
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <utility>
#include <queue>
#include <string>

class Intcode {
public:
	typedef long long ll;

	Intcode(std::istream& stream) {
		for (Intcode::ll i = 0LL, value; stream >> value;) {
			program_[i++] = value;
			stream.ignore(); // Ignore comma
		}
	}

	Intcode(const Intcode& intcode) {
		running_ = intcode.running_;
		program_ = intcode.program_;
		inputs_ = intcode.inputs_;
		pc_ = intcode.pc_;
		rb_ = intcode.rb_;
	}

	bool IsRunning() const {
		return running_;
	}

	bool HasInput() {
		return !inputs_.empty();
	}

	void AddInput(ll input) {
		inputs_.push(input);
	}

	void AddInput(std::string string) {
		for (char c : string) {
			AddInput((ll)c);
		}
	}

	ll Execute() {
		while (running_) {
			ll op_code = program_[pc_] % 100;
			std::vector<ll> params;
			switch (op_code) {
				case 1: // Add
					GetParams(params, 3, 2);
					program_[params[2]] = params[0] + params[1];
					pc_ += 4;
					break;
				case 2: // Multiply
					GetParams(params, 3, 2);
					program_[params[2]] = params[0] * params[1];
					pc_ += 4;
					break;
				case 3: // Input
					GetParams(params, 1, 0);
					program_[params[0]] = inputs_.front();
					inputs_.pop();
					pc_ += 2;
					break;
				case 4: // Output
					GetParams(params, 1, -1);
					pc_ += 2;
					return params[0];
					break;
				case 5: // Jump-if-true
					GetParams(params, 2, -1);
					if (params[0] != 0) {
						pc_ = params[1];
					} else {
						pc_ += 3;
					}
					break;
				case 6: // Jump-if-false
					GetParams(params, 2, -1);
					if (params[0] == 0) {
						pc_ = params[1];
					} else {
						pc_ += 3;
					}
					break;
				case 7: // Less than
					GetParams(params, 3, 2);
					if (params[0] < params[1]) {
						program_[params[2]] = 1;
					} else {
						program_[params[2]] = 0;
					}
					pc_ += 4;
					break;
				case 8: // Equals
					GetParams(params, 3, 2);
					if (params[0] == params[1]) {
						program_[params[2]] = 1;
					} else {
						program_[params[2]] = 0;
					}
					pc_ += 4;
					break;
				case 9: // Relative base
					GetParams(params, 1, -1);
					rb_ += params[0];
					pc_ += 2;
					break;
				case 99: // Terminate
					running_ = false;
					//pc_ += 1;
					break;
			}
		}
		return -1;
	}

	void GetParams(std::vector<ll>& params, int num_params, int write_param) {	
		ll modes = program_[pc_] / 100;
		for (int i = 0; i < num_params; ++i) {
			ll param = program_[pc_+i+1];
			ll mode = GetDigit(modes, i);
			ll value;
			if (i == write_param) {
				value = param;
				if (mode == 2) {
					value += rb_;
				}
			} else {
				if (mode == 0) { // Position mode
					value = program_[param];
				} else if (mode == 1) { // Immediate mode
					value = param;
				} else { // Relative mode
					value = program_[param + rb_];
				}
			}
			params.push_back(value);
		}
	}

	static ll GetDigit(ll value, int n) {
		ll div = 1;
		for (int i = 0; i < n; ++i) {
			div *= 10LL;
		}
		return (value / div) % 10LL;
	}

private:
	bool running_ = true;
	std::unordered_map<ll, ll> program_;
	std::queue<ll> inputs_;
	ll pc_ = 0; // Program counter
	ll rb_ = 0; // Relative base

};

void FeedInput(Intcode& intcode, int bits) {
	intcode.AddInput("east\n");
	if (bits & (1 << 0)) {
		intcode.AddInput("take semiconductor\n");
	}
	intcode.AddInput("east\n");
	if (bits & (1 << 1)) {
		intcode.AddInput("take ornament\n");
	}
	intcode.AddInput("west\n");
	intcode.AddInput("west\n");

	intcode.AddInput("north\n");
	intcode.AddInput("north\n");
	intcode.AddInput("north\n");
	if (bits & (1 << 2)) {
		intcode.AddInput("take mutex\n");
	}
	intcode.AddInput("south\n");
	intcode.AddInput("south\n");
	intcode.AddInput("east\n");
	intcode.AddInput("north\n");
	if (bits & (1 << 3)) {
		intcode.AddInput("take loom\n");
	}
	intcode.AddInput("south\n");
	intcode.AddInput("west\n");
	intcode.AddInput("south\n");

	intcode.AddInput("west\n");
	intcode.AddInput("west\n");

	if (bits & (1 << 4)) {
		intcode.AddInput("take sand\n");
	}
	intcode.AddInput("south\n");
	intcode.AddInput("east\n");
	if (bits & (1 << 5)) {
		intcode.AddInput("take asterisk\n");
	}
	intcode.AddInput("north\n");
	if (bits & (1 << 6)) {
		intcode.AddInput("take wreath\n");
	}
	intcode.AddInput("south\n");
	intcode.AddInput("west\n");
	intcode.AddInput("north\n");

	intcode.AddInput("north\n");
	if (bits & (1 << 7)) {
		intcode.AddInput("take dark matter\n");
	}
	intcode.AddInput("east\n");
	intcode.AddInput("east\n");
}

int main() {
	Intcode initial_intcode(std::cin);
	/*std::ifstream input_file("input");
	Intcode initial_intcode(input_file);
	input_file.close();*/

	const std::string failure_output = "A loud, robotic voice says \"Alert!";
	const std::string success_output = "\"Oh, hello!";

	for (int bits = 0; bits < (1 << 8); ++bits) {
		Intcode intcode(initial_intcode);
		FeedInput(intcode, bits);

		while (intcode.IsRunning()) {
			std::string line;
			do {
				line += (char)intcode.Execute();
			} while (line.back() != '\n');

			// Check if item selection is correct
			if (line.substr(0, failure_output.length()) == failure_output) {
				break;
			} else if (line.substr(0, success_output.length()) == success_output) {
				int i_begin = 51;
				int i_end = line.find(" on ") - 1;
				std::cout << line.substr(i_begin, i_end - i_begin + 1) << std::endl;
				return 0;
			}
			
			// User input (make sure to read puzzle input from file instead of std::cin)
			/* if (!intcode.HasInput() && line == "Command?\n") {
				std::string user_input;
				std::getline(std::cin, user_input);
				intcode.AddInput(user_input + '\n');
			} */
		}
	}

	return 0;
}
