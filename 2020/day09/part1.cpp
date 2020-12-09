#include <iostream>
#include <unordered_map>
#include <vector>

int main() {
	std::unordered_map<long long, int> prev;
	std::vector<long long> list;
	for (long long num; list.size() < 25 && std::cin >> num;) {
		list.push_back(num);
		if (prev.find(num) == prev.end())
			prev[num] = 1;
		else
			++prev[num];
	}

	for (long long num; std::cin >> num;) {
		bool valid = false;
		for (auto it : prev) {
			long long sub = num - it.first;
			if (sub != it.first && prev.find(sub) != prev.end()) {
				valid = true;
				break;
			}
		}
		if (valid) {
			long long del = list[list.size() - 25];
			list.push_back(num);
			// Insert new
			if (prev.find(num) == prev.end())
				prev[num] = 1;
			else
				++prev[num];
			// Delete old
			if (prev[del] > 1)
				--prev[del];
			else
				prev.erase(del);
		} else {
			std::cout << num << std::endl;
			break;
		}
	}

	return 0;
}
