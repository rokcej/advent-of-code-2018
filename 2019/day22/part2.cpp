/*
Inspired by u/etotheipi1's solution
https://www.reddit.com/r/adventofcode/comments/ee0rqi/2019_day_22_solutions/fbnifwk/

This solution requires 128-bit integers to work.
Although 128-bit integers are not part of the C++ standard (yet), GCC provides the data type __int128 on 64-bit arhitectures.
If your compiler does not support __int128, God help you.
*/

#include <iostream>
#include <string>
#include <vector>

typedef __int128 i128;

// Compute a % m, always return a positive value
i128 mod(i128 a, i128 m) {
	if (a < 0LL) {
		return a % m + m;
	}
	return a % m;
}

// Compute (a ^ b) % m
// https://stackoverflow.com/a/8498251
i128 mod_pow(i128 a, i128 b, i128 m) {
	a = mod(a, m);
	i128 result = 1LL;
	while (b > 0LL) {
		if (b & 1LL) {
			result = (result * a) % m;
		}
		a = (a * a) % m;
		b >>= 1LL;
	}
	return result;
}

// Compute (a * b) % m
// https://stackoverflow.com/a/12171020
i128 mod_mul(i128 a, i128 b, i128 m) {
	a = mod(a, m);
	b = mod(b, m);
	i128 result = 0LL;
	while (a != 0LL) {
		if (a & 1) {
			result = (result + b) % m;
		}
		b = (b << 1) % m;
		a >>= 1;
	}
	return result;
}

// Extended Euclidean algorithm
// https://stackoverflow.com/a/32241043/4808188
i128 egcd(i128 a, i128 b, i128& x, i128& y) {
	if (b == 0LL) {
		x = 1LL;
		y = 0LL;
		return a;
	}
	i128 x1, y1;
	i128 gcd = egcd(b, a % b, x1, y1);
	x = y1;
	y = x1 - (a / b) * y1;
	return gcd;
}

// Modular multiplicative inverse
// https://stackoverflow.com/a/9758173
i128 mod_inv(i128 a, i128 m) {
	a = mod(a, m);
	i128 x, y;
	i128 gcd = egcd(a, m, x, y);
	if (gcd != 1LL) {
		std::cerr << "Modular inverse does not exist!" << std::endl;
	}
	return (x % m + m) % m;
}

i128 reverse_shuffle(i128 position, const i128 count, const std::vector<std::string>& lines) {
	for (int i = lines.size() - 1; i >= 0; --i) {
		const std::string& line = lines[i];
		if (line[0] == 'c') {
			// Reverse cut
			i128 cut = std::stoll(line.substr(4));
			position = (position + count + cut) % count;
		} else if (line[5] == 'w') {
			// Reverse deal with increment
			i128 increment = std::stoll(line.substr(20));
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

	const i128 count = 119315717514047LL;  // Number of cards
	const i128 position = 2020LL;          // Card position
	const i128 repeat = 101741582076661LL; // Number of times to shuffle the cards

	// Shuffling is a linear transformation (and therefore reverse shuffling as well)
	// There exist a and b, such that f(card) = (a * card + b) % count
	i128 i = position;                            // i
	i128 fi = reverse_shuffle(i, count, lines);   // f(i)
	i128 ffi = reverse_shuffle(fi, count, lines); // f(f(i))

	// f(i) = a * i + b
	// f(f(i)) = a * f(i) + b
	// ----------------------
	// a * (i - f(i)) = f(i) - f(f(i))
	// a = (f(i) - f(f(i))) / (i - f(i))
	// b = f(i) - a * i
	i128 a = mod_mul(fi - ffi, mod_inv(i - fi, count), count);
	i128 b = mod(fi - mod_mul(a, i, count), count);

	// f^n(i) = f(f(f(...f(i))))
	// f^n(i) = a^n*i + a^(n-1)*b + ... + a^1*b + b
	// f^n(i) = a^n*i + (a^(n-1) + ... + a + 1) * b
	// f^n(i) = a^n*i + (a^n - 1) / (a - 1) * b
	i128 fni = (
		mod_mul(mod_pow(a, repeat, count), i, count) + // a^n*i
		mod_mul(mod_mul((mod_pow(a, repeat, count) - 1LL), mod_inv(a - 1LL, count), count), b, count) // (a^n-1)/(a-1)*b
	) % count;

	long long result = static_cast<long long>(fni);
	std::cout << result << std::endl;

	return 0;
}
