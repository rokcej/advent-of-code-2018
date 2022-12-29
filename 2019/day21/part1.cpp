#include <iostream>
#include <vector>
#include <unordered_map>
#include <utility>
#include <queue>

class Intcode {
public:
	typedef long long ll;

	Intcode(std::istream& stream) {
		for (Intcode::ll i = 0LL, value; stream >> value;) {
			program_[i++] = value;
			stream.ignore(); // Ignore comma
		}
	}

	Intcode(const std::unordered_map<ll, ll>& program) {
		program_ = program;
	}

	bool IsRunning() const {
		return running_;
	}

	void AddInput(ll input) {
		inputs_.push(input);
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

int main() {
	Intcode intcode(std::cin);
	while (intcode.IsRunning()) {
		char c = (char)intcode.Execute();
		// std::cout << c;
		if (c == '\n') {
			break;
		}
	}

	// Jump when (!A || !B || !C) && D
	std::string input = "NOT J J\nAND A J\nAND B J\nAND C J\nNOT J J\nAND D J\nWALK\n";
	for (char c : input) {
		intcode.AddInput((Intcode::ll)c);
	}

	while (intcode.IsRunning()) {
		Intcode::ll output = intcode.Execute();
		if (output >= 128) {
			std::cout << output << std::endl;
			break;
		}
		// std::cout << (char)output;
	}

	return 0;
}
