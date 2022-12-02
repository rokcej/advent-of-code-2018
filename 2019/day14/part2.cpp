#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>

std::unordered_map<std::string, std::pair<long long, std::vector<std::pair<std::string, long long>>>> reactions;
std::vector<std::pair<std::string, long long>> inputs;

long long compute_ore(long long fuel) {
	long long ore = 0LL;
	std::unordered_map<std::string, long long> extra;
	std::unordered_map<std::string, long long> required;
	required["FUEL"] = fuel;

	while (!required.empty()) {
		auto req_iter = required.begin();
		std::string req_name = req_iter->first;
		long long req_num = req_iter->second;
		required.erase(req_iter);

		if (req_name == "ORE") {
			ore += (long long)req_num;
			continue;
		}

		long long extra_num = extra[req_name];
		if (extra_num > 0LL) {
			if (extra_num >= req_num) {
				extra[req_name] -= req_num;
				continue;
			} else {
				req_num -= extra_num;
				extra[req_name] = 0LL;
			}
		}

		auto reaction = reactions[req_name];
		long long out_num = reaction.first;
		long long factor = (req_num - 1) / out_num + 1;
		extra[req_name] = factor * out_num - req_num;

		for (const auto& in : reaction.second) {
			required[in.first] += factor * in.second;
		}
	}

	return ore;
}

int main() {
	for (long long num; std::cin >> num;) {
		std::string name;
		std::cin >> name;

		if (name.back() == ',') {
			name = name.substr(0, name.length() - 1);
			inputs.push_back(std::make_pair(name, num));
			continue;
		}
		inputs.push_back(std::make_pair(name, num));

		std::cin >> name >> num >> name; // First one is a dummy to skip "=>"
		reactions[name] = std::make_pair(num, inputs);
		inputs.clear();
	}

	// Find lower and upper bound
	long long fuel = 1;
	while (compute_ore(fuel) <= 1000000000000LL) {
		fuel *= 2LL;
	}
	long long lower_equal = fuel / 2;
	long long upper = fuel;

	// Find maximum value with bisection
	long long ctr = 0;
	while (upper > lower_equal + 1LL) {
		fuel = (lower_equal + upper) / 2LL;
		if (compute_ore(fuel) <= 1000000000000LL) {
			lower_equal = fuel;
		} else {
			upper = fuel;
		}
	}

	std::cout << lower_equal << std::endl;

	return 0;
}
