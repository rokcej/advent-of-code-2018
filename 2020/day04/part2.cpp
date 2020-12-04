#include <iostream>
#include <string>
#include <sstream>
#include <unordered_set>
// #include <regex>

bool isNumber(const std::string &s) {
	// return std::regex_match(s, std::regex("[0-9]+"));

	if (s.empty())
		return false;
	for (char c : s)
		if (c < '0' || c > '9') return false;
	return true;
}

bool isNumberBetween(const std::string &s, int min, int max) {
	if (isNumber(s)) {
		int num = std::stoi(s);
		return num >= min && num <= max;
	} else {
		return false;
	}
}

int main() {
	std::unordered_set<std::string> required({"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"});
	std::unordered_set<std::string> eye_colors({"amb", "blu", "brn", "gry", "grn", "hzl", "oth"});

	int n_valid = 0;
	std::unordered_set<std::string> included;

	std::string line;
	while (std::getline(std::cin, line)) {
		if (line.length() == 0) {
			if (required.size() == included.size())
				++n_valid;
			included.clear();
		} else {
			std::istringstream iss(line);
			std::string token;
			while (iss >> token) {
				int idx = token.find(':');
				std::string key = token.substr(0, idx);
				std::string value = token.substr(idx + 1);

				bool valid = false;

				if (key.compare("byr") == 0) {
					if (isNumberBetween(value, 1920, 2002))
						valid = true;
				} else if (key.compare("iyr") == 0) {
					if (isNumberBetween(value, 2010, 2020))
						valid = true;
				} else if (key.compare("eyr") == 0) {
					if (isNumberBetween(value, 2020, 2030))
						valid = true;
				} else if (key.compare("hgt") == 0) {
					if (value.length() >= 3) {
						std::string unit = value.substr(value.length() - 2);
						std::string amount = value.substr(0, value.length() - 2);
						if (unit.compare("cm") == 0) {
							if (isNumberBetween(amount, 150, 193))
								valid = true;
						} else if (unit.compare("in") == 0) {
							if (isNumberBetween(amount, 59, 76))
								valid = true;
						}
					}
				} else if (key.compare("hcl") == 0) {
					// if (std::regex_match(value, std::regex("#[0-9a-f]{6}")))
					// 	valid = true;

					if (value.length() == 7 && value[0] == '#') {
						valid = true;
						for (int i = 1; i < 7; ++i) {
							if (!(value[i] >= '0' && value[i] <= '9' || value[i] >= 'a' && value[i] <= 'f')) {
								valid = false;
								break;
							}
						}
					}
				} else if (key.compare("ecl") == 0) {
					if (eye_colors.find(value) != eye_colors.end())
						valid = true;
				} else if (key.compare("pid") == 0) {
					if (value.length() == 9 && isNumber(value) && value.compare("000000000") >= 0 && value.compare("999999999") <= 0)
						valid = true;
				}

				if (valid)
					included.insert(key);
			}
		}
	}
	if (required.size() == included.size())
		++n_valid;
	included.clear();

	std::cout << n_valid << std::endl;

	return 0;
}
