#include <iostream>
#include <vector>
#include <algorithm>

int main() {
	std::vector<int> list = { 0 };
	for (int num; std::cin >> num;)
		list.push_back(num);
	std::sort(list.begin(), list.end());

	std::vector<long long> count(list.size(), 0LL);
	count[list.size() - 1] = 1LL;
	for (int i = count.size() - 2; i >= 0; --i) {
		for (int j = i + 1; j < count.size() && list[j] - list[i] <= 3; ++j)
			count[i] += count[j];
	}

	std::cout << count[0] << std::endl;

	return 0;
}
