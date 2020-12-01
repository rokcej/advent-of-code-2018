#include <iostream>
#include <vector>

int main() {
	std::vector<int> vals;
	for (int val; std::cin >> val;)
		vals.push_back(val);

	for (int i = 0; i < vals.size(); ++i) {
		for (int j = i + 1; j < vals.size(); ++j) {
			for (int k = j + 1; k < vals.size(); ++k) {
				if (vals[i] + vals[j] + vals[k] == 2020) {
					std::cout << vals[i] * vals[j] * vals[k];
					return 0;
				}
			}
		}
	}

	return 0;
}
