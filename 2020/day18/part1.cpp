#include <iostream>
#include <string>

long long eval(std::string expr) {
	long long value = 0LL;
	char op = '+';
	for (int pos = 0; pos < expr.length(); ++pos) {
		char c = expr[pos];

		if (c == '+' || c == '*') { // Select operation
			op = c;
		} else if (c >= '0' && c <= '9') { // If digit, read whole number
			int end = pos;
			while (end + 1 < expr.length() && expr[end + 1] >= '0' && expr[end + 1] <= '9')
				++end;
			long long term = std::stoll(expr.substr(pos, end + 1 - pos));
			value = (op == '+') ? (value + term) : (value * term);
			pos = end;
		} else if (c == '(') { // If parenthesis, evaluate expression inside
			int end = pos + 1;
			for (int depth = 1; end < expr.length(); ++end) {
				if (expr[end] == '(') {
					++depth;
				} else if (expr[end] == ')') {
					if (--depth == 0)
						break;
				}
			}
			long long term = eval(expr.substr(pos + 1, end - (pos + 1)));
			value = (op == '+') ? (value + term) : (value * term);
			pos = end;
		}
	}

	return value;
}

int main() {
	long long result = 0LL;
	for (std::string line; std::getline(std::cin, line) && !line.empty();)
		result += eval(line);

	std::cout << result << std::endl;

	return 0;
}
