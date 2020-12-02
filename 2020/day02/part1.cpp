#include <iostream>
#include <string>

int main() {
	int min, max;
	char letter, temp;
	std::string password;

	int valid = 0;

	while (std::cin >> min >> temp >> max >> letter >> temp >> password) {
		int count = 0;
		for (int i = 0; i < password.length(); ++i) {
			if (password[i] == letter)
				++count;
		}
		if (count >= min && count <= max)
			++valid;
	}

	std::cout << valid << std::endl;

	return 0;
}
