#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <utility>
#include <array>

// Greatest common divisor
long long gcd(long long a, long long b) {
	while (b > 0LL) {
		long long a_old = a;
		a = b;
		b = a_old % b;
	}
	return a;
}
// Least common multiple
long long lcm(long long a, long long b) {
	return std::abs(a * b) / gcd(a, b);
}

int main() {
	std::vector<int> ids; // Shuttle bus IDs
	std::vector<int> offs; // Delays

	// Read input
	std::string line;
	std::cin >> line >> line;

	// Parse input
	int count = 0;
	for (size_t pos = 0, next; pos < line.length(); pos = next + 1) {
		next = line.find(',', pos);
		if (next == std::string::npos)
			next = line.length();
		if (line[pos] != 'x') {
			ids.push_back(std::stol(line.substr(pos, next - pos)));
			offs.push_back(count);
		}
		++count;
	}

	// Find LCM of IDs
	long long N = 1LL;
	for (auto id : ids)
		N = lcm(N, id);

	// Compute sum parts
	std::vector<std::array<long long, 2>> parts;
	for (int i = 1; i < ids.size(); ++i) {
		long long coeff = N / ids[i];
		int k = 0;
		while ((coeff * k + offs[i]) % ids[i] != 0)
			++k;
		parts.push_back({coeff * k, -coeff * (ids[i] - k)});
	}

	// Find smallest positive sum
	long long result;
	for (int perm = 0; perm < (1 << parts.size()); ++perm) { // Permutations
		long long sum = 0LL;
		for (int i = 0; i < parts.size(); ++i)
			sum += parts[i][(perm >> i) & 1]; // Magic
		if (sum >= 0LL && sum < result || perm == 0)
			result = sum;
	}

	std::cout << result << std::endl;

	return 0;
}
