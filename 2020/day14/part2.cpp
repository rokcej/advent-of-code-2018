#include <iostream>
#include <string>
#include <unordered_map>

std::unordered_map<long long, long long> mem;
std::string mask;

void write(long long& addr, const long long& num, int depth) {
	if (depth == mask.length()) {
		mem[addr] = num;
		return;
	}

	char bit = mask[mask.length() - 1 - depth];
	if (bit == 'X') {
		addr &= ~(1LL << depth);
		write(addr, num, depth + 1);
		addr |= 1LL << depth;
		write(addr, num, depth + 1);
	} else {
		if (bit == '1')
			addr |= 1LL << depth;
		write(addr, num, depth + 1);
	}
}

int main() {
	for (std::string var, val, temp; std::cin >> var >> temp >> val;) {
		if (var.compare("mask") == 0) {
			mask = val;
		} else {
			long long addr = std::stoll(var.substr(4, var.length() - 5));
			long long num = std::stoll(val);
			write(addr, num, 0);
		}
	}

	long long result = 0LL;
	for (auto pair : mem)
		result += pair.second;

	std::cout << result << std::endl;

	return 0;
}
