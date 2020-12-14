#include <iostream>
#include <string>
#include <unordered_map>

int main() {
	std::unordered_map<long long, long long> mem;
	std::string mask;

	for (std::string var, val, temp; std::cin >> var >> temp >> val;) {
		if (var.compare("mask") == 0) {
			mask = val;
		} else {
			long long addr = std::stoll(var.substr(4, var.length() - 5));
			long long num = std::stoll(val);

			for (int i = 0; i < mask.length(); ++i) {
				char bit = mask[mask.length() - 1 - i];
				if (bit == '0')
					num &= ~(1LL << i);
				else if (bit == '1')
					num |= 1LL << i;
			}
			mem[addr] = num;
		}
	}
	
	long long result = 0LL;
	for (auto pair : mem)
		result += pair.second;

	std::cout << result << std::endl;

	return 0;
}
