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

	// Copy constructor
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

	void AddInput(ll input) {
		inputs_.push(input);
		input_overflow_ = false;
	}

	ll GetOutput() {
		return output_;
	}

	ll Execute() {
		while (running_) {
			if (ExecuteStep()) {
				return output_;
			}
		}
		return output_;
	}

	bool ExecuteStep() {
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
				if (inputs_.size() > 0) {
					program_[params[0]] = inputs_.front();
					inputs_.pop();
				} else {
					program_[params[0]] = -1LL;
					input_overflow_ = true;
				}
				pc_ += 2;
				break;
			case 4: // Output
				GetParams(params, 1, -1);
				pc_ += 2;
				output_ = params[0];
				return true;
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
		return false;
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

public:
	bool input_overflow_ = false;

private:
	bool running_ = true;
	std::unordered_map<ll, ll> program_ = {};
	std::queue<ll> inputs_ = {};
	ll output_ = -1LL;
	ll pc_ = 0; // Program counter
	ll rb_ = 0; // Relative base

};


int main() {
	Intcode intcode(std::cin);
	
	std::vector<Intcode> computers;
	std::vector<std::vector<Intcode::ll>> outputs;
	for (Intcode::ll i = 0; i < 50; ++i) {
		computers.emplace_back(intcode);
		computers[i].AddInput(i);
		outputs.emplace_back();
	}
	
	Intcode::ll nat[2];
	Intcode::ll Y_prev;
	int idle_count = 0;

	while (true) {
		bool idle = true;
		
		for (int i = 0; i < computers.size(); ++i) {
			Intcode& comp = computers[i];
			auto& output = outputs[i];

			if (!comp.ExecuteStep()) {
				idle = idle && comp.input_overflow_;
				continue;
			}
			idle = false;

			output.push_back(comp.GetOutput());
			if (output.size() != 3) {
				continue;
			}

			Intcode::ll j = output[0], X = output[1], Y = output[2];
			if (j == 255LL) {
				nat[0] = X;
				nat[1] = Y;
			} else {
				computers[j].AddInput(X);
				computers[j].AddInput(Y);
			}
			output.clear();
		}

		if (idle) {
			computers[0].AddInput(nat[0]);
			computers[0].AddInput(nat[1]);
			if (idle_count > 0 && Y_prev == nat[1]) {
				break;
			}
			Y_prev = nat[1];
			++idle_count;
		}
	}

	std::cout << Y_prev << std::endl;

	return 0;
}
