/*
Inspired by u/etotheipi1's solution
https://www.reddit.com/r/adventofcode/comments/ee0rqi/2019_day_22_solutions/fbnifwk/

Special functions were used for modulo mutiplication and exponentiation to avoid overflow
*/

#include <iostream>
#include <string>
#include <vector>

// Compute a % m, always return a positive value
long long mod(long long a, long long m) {
	if (a < 0LL) {
		return a % m + m;
	}
	return a % m;
}

// Compute (a * b) % m
// https://stackoverflow.com/a/12171020
long long mod_mul(long long a, long long b, long long m) {
	a = mod(a, m);
	b = mod(b, m);
	long long result = 0LL;
	while (a != 0LL) {
		if (a & 1) {
			result = (result + b) % m;
		}
		b = (b << 1) % m;
		a >>= 1;
	}
	return result;
}

// Compute (a ^ b) % m
// Slow, but fairly safe
long long mod_pow(long long a, long long b, long long m) {
	// Find index of highest set bit
	int highest_bit = 0;
	for (int i = 0; i < sizeof(b) * 8 - 1; ++i) {
		if (b & ((long long)1 << i)) {
			highest_bit = i;
		}
	}
	// Compute quadratic powers of a (a^1, a^2, a^4, a^8, ...)
	std::vector<long long> powers(highest_bit + 1, 0);
	powers[0] = a;
	for (int i = 1; i <= highest_bit; ++i) {
		powers[i] = mod_mul(powers[i-1], powers[i-1], m);
	}
	// Multiply result by powers of a that correspond to set bits of b
	long long result = 1LL;
	for (int i = 0; i <= highest_bit; ++i) {
		if (b & ((long long)1 << i)) {
			result = mod_mul(result, powers[i], m);
		}
	}
	return result;
}

// Extended Euclidean algorithm
// https://stackoverflow.com/a/32241043/4808188
long long egcd(long long a, long long b, long long& x, long long& y) {
	if (b == 0LL) {
		x = 1LL;
		y = 0LL;
		return a;
	}
	long long x1, y1;
	long long gcd = egcd(b, a % b, x1, y1);
	x = y1;
	y = x1 - (a / b) * y1;
	return gcd;
}

// Modular multiplicative inverse
// https://stackoverflow.com/a/9758173
long long mod_inv(long long a, long long m) {
	a = mod(a, m);
	long long x, y;
	long long gcd = egcd(a, m, x, y);
	if (gcd != 1LL) {
		std::cerr << "Modular inverse does not exist!" << std::endl;
	}
	return (x % m + m) % m;
}

long long reverse_shuffle(long long position, const long long count, const std::vector<std::string>& lines) {
	for (int i = lines.size() - 1; i >= 0; --i) {
		const std::string& line = lines[i];
		if (line[0] == 'c') {
			// Reverse cut
			long long cut = std::stoll(line.substr(4));
			position = (position + count + cut) % count;
		} else if (line[5] == 'w') {
			// Reverse deal with increment
			long long increment = std::stoll(line.substr(20));
			position = mod_mul(mod_inv(increment, count), position, count);
		} else {
			// Reverse deal into new stack
			position = (count - 1LL) - position;
		}
	}
	return position;
}

int main() {
	std::vector<std::string> lines;
	for (std::string line; std::getline(std::cin, line);) {
		lines.push_back(line);
	}

	const long long count = 119315717514047LL;  // Number of cards
	const long long position = 2020LL;          // Card position
	const long long repeat = 101741582076661LL; // Number of times to shuffle the cards

	// Shuffling is a linear transformation (and therefore reverse shuffling as well)
	// There exist a and b, such that f(card) = (a * card + b) % count
	long long i = position;                            // i
	long long fi = reverse_shuffle(i, count, lines);   // f(i)
	long long ffi = reverse_shuffle(fi, count, lines); // f(f(i))

	// f(i) = a * i + b
	// f(f(i)) = a * f(i) + b
	// ----------------------
	// a * (i - f(i)) = f(i) - f(f(i))
	// a = (f(i) - f(f(i))) / (i - f(i))
	// b = f(i) - a * i
	long long a = mod_mul(fi - ffi, mod_inv(i - fi, count), count);
	long long b = mod(fi - mod_mul(a, i, count), count);

	// f^n(i) = f(f(f(...f(i))))
	// f^n(i) = a^n*i + a^(n-1)*b + ... + a^1*b + b
	// f^n(i) = a^n*i + (a^(n-1) + ... + a + 1) * b
	// f^n(i) = a^n*i + (a^n - 1) / (a - 1) * b
	long long fni = (
		mod_mul(mod_pow(a, repeat, count), i, count) + // a^n*i
		mod_mul(mod_mul((mod_pow(a, repeat, count) - 1LL), mod_inv(a - 1LL, count), count), b, count) // (a^n-1)/(a-1)*b
	) % count;

	long long result = static_cast<long long>(fni);
	std::cout << result << std::endl;

	return 0;
}
