#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <utility>

long long gcd(long long a, long long b) {
	long long temp;
	while (b > 0LL) {
		temp = a;
		a = b;
		b = temp % b;
	}
	return a;
}

long long lcm(long long a, long long b) {
	return std::abs(a * b) / gcd(a, b);
}

int main() {
	std::vector<int> ids;
	std::vector<int> offs;

	std::string line;
	std::cin >> line >> line;

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

	long long N = 1LL;
	for (auto n : ids)
		N = lcm(N, n);

	std::vector<std::pair<long long, long long>> parts;

	long long result = 0LL;
	for (int i = 1; i < ids.size(); ++i) {
		long long coeff = N / ids[i];
		int k = 0;
		while ((coeff * k + offs[i]) % ids[i] != 0)
			++k;
		result += coeff * k;
		parts.emplace_back(coeff * k, -coeff * (ids[i] - k));
	}

	for (int i = 1; i < (1 << parts.size()); ++i) {
		long long sum = 0LL;
		for (int j = 0; j < parts.size(); ++j) {
			if ((1 << j) & i)
				sum += parts[j].second;
			else
				sum += parts[j].first;
		}
		if (sum >= 0LL && sum < result)
			result = sum;
	}

	std::cout << result << std::endl;

	return 0;
}
