#include <iostream>
#include <string>

int main() {
	std::string minStr, maxStr;
	std::getline(std::cin, minStr, '-');
	std::getline(std::cin, maxStr);

	int len = minStr.length();

	int min = std::stoi(minStr);
	int max = std::stoi(maxStr);

	int count = 0;
	for (int num = min; num <= max; ++num) {
		std::string numStr = std::to_string(num);
		char minDigit = numStr[0];
		bool correct = false;
		for (int i = 1; i < len; ++i) {
			if (numStr[i] < minDigit) {
				correct = false;
				break;
			} else if (numStr[i] > minDigit) {
				minDigit = numStr[i];
			}
			if (numStr[i] == numStr[i-1])
				correct = true;
		}
		if (correct)
			++count;
	}

	std::cout << count << std::endl;

	return 0;
}
