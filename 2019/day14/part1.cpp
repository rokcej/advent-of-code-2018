#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>

int main() {
	std::unordered_map<std::string, std::pair<int, std::vector<std::pair<std::string, int>>>> reactions;
	std::vector<std::pair<std::string, int>> inputs;

	for (int num; std::cin >> num;) {
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

	int ore = 0;
	std::unordered_map<std::string, int> extra;
	std::unordered_map<std::string, int> required;
	required["FUEL"] = 1;

	while (!required.empty()) {
		auto req_iter = required.begin();
		std::string req_name = req_iter->first;
		int req_num = req_iter->second;
		required.erase(req_iter);

		if (req_name == "ORE") {
			ore += req_num;
			continue;
		}

		int extra_num = extra[req_name];
		if (extra_num > 0) {
			if (extra_num >= req_num) {
				extra[req_name] -= req_num;
				continue;
			} else {
				req_num -= extra_num;
				extra[req_name] = 0;
			}
		}

		auto reaction = reactions[req_name];
		int out_num = reaction.first;
		int factor = (req_num - 1) / out_num + 1;
		extra[req_name] = factor * out_num - req_num;

		for (const auto& in : reaction.second) {
			required[in.first] += factor * in.second;
		}
	}

	std::cout << ore << std::endl;

	return 0;
}
