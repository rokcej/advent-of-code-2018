#include <iostream>
#include <vector>
#include <algorithm>

int main() {
	std::vector<int> list = { 0 };
	for (int num; std::cin >> num;)
		list.push_back(num);
	std::sort(list.begin(), list.end());

	int diff[4] = { 0, 0, 0, 1 };
	for (int i = 1; i < list.size(); ++i)
		++diff[list[i] - list[i-1]];

	std::cout << diff[1] * diff[3] << std::endl;

	return 0;
}
