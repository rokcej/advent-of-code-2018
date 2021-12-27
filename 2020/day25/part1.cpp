#include <iostream>

const long long MOD = 20201227LL;

int main() {
	long long public_keys[2];
	std::cin >> public_keys[0] >> public_keys[1];

	long long loop_sizes[2];
	for (int i = 0; i < 2; ++i) {
		long long value = 1LL;
		for (int loop_size = 1;; ++loop_size) {
			value = value * 7LL % MOD;
			if (value == public_keys[i]) {
				loop_sizes[i] = loop_size;
				break;
			}
		}
	}

	long long encryption_keys[2];
	for (int i = 0; i < 2; ++i) {
		long long value = 1LL;
		for (int loop = 0; loop < loop_sizes[i]; ++loop) {
			value = (value * public_keys[1-i]) % MOD;
		}
		encryption_keys[i] = value;
	}
	if (encryption_keys[0] == encryption_keys[1]) {
		std::cout << encryption_keys[0] << std::endl;
	} else {
		std::cout << "Incorrect encryption keys" << std::endl;
	}

	return 0;
}
