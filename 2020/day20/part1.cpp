#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <array>

// Equal
bool eq(const std::string& a, const std::string& b) {
	return a.compare(b) == 0;
}
// Equal in reverse
bool eqr(const std::string& a, const std::string& b) {
	int len = a.length();
	for (int i = 0; i < len; ++i) {
		if (a[i] != b[len - 1 - i])
			return false;
	}
	return true;
}

int main() {
	std::unordered_map<int, std::array<std::string, 4>> edges;
	std::unordered_map<int, std::vector<std::string>> images;

	for (std::string line; std::getline(std::cin, line);) {
		int id = std::stoi(line.substr(5, line.length() - 6));
		while (std::getline(std::cin, line) && !line.empty()) {
			images[id].push_back(line);
		}
	}

	for (auto el : images) {
		int id = el.first;
		edges[id][0] = el.second.front();
		edges[id][2] = el.second.back();
		for (int i = 0; i < el.second.size(); ++i) {
			edges[id][1] += el.second[i].front();
			edges[id][3] += el.second[i].back();
		}
	}

	long long result = 1LL;
	for (auto el1 : edges) {
		int id1 = el1.first;
		int count = 0;
		for (auto el2 : edges) {
			int id2 = el2.first;
			if (id1 == id2)
				continue;
			for (auto e1 : el1.second) {
				for (auto e2 : el2.second) {
					if (eq(e1, e2) || eqr(e1, e2)) {
						++count;
						break;
					}
				}
			}
		}
		if (count == 2)
			result *= id1;
	}

	std::cout << result << std::endl;

	return 0;
}
