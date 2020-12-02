#include <iostream>
#include <string>

int main() {
	int i1, i2;
	char letter, temp;
	std::string password;

	int valid = 0;

	while (std::cin >> i1 >> temp >> i2 >> letter >> temp >> password) {
		if ((password[i1 - 1] == letter) ^ (password[i2 - 1] == letter))
			++valid;
	}

	std::cout << valid << std::endl;

	return 0;
}
