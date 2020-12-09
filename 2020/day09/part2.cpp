#include <iostream>
#include <unordered_map>
#include <queue>

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

	long long x;

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
			x = num;
			break;
		}
	}

	long long sum = 0LL;
	for (int i = 0, j = 0; j < list.size(); ++j) {
		sum += list[j];

		while (sum > x && i <= j)
			sum -= list[i++];

		if (sum == x) {
			long long min = list[i], max = list[i];
			for (int k = i + 1; k < j; ++k) {
				if (list[k] < min) min = list[k];
				else if (list[k] > max) max = list[k];
			}
			std::cout << min + max << std::endl;
			break;
		}
	}

	return 0;
}
