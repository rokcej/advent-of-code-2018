#include <iostream>
#include <string>
#include <queue>

int main() {
	std::deque<int> players[2];

	int i_input = 0;
	for (std::string line; std::getline(std::cin, line);) {
		if (line[0] == 'P') {
			continue;
		} else if (line.empty()) {
			++i_input;
			continue;
		}
		players[i_input].push_back(std::stoi(line));
	}

	while (!players[0].empty() && !players[1].empty()) {
		int cards[2];
		for (int i = 0; i < 2; ++i) {
			cards[i] = players[i].front();
			players[i].pop_front();
		}
		int i_winner = cards[0] < cards[1];
		players[i_winner].push_back(cards[i_winner]);
		players[i_winner].push_back(cards[1-i_winner]);
	}

	int winner = players[0].empty();
	int score = 0;
	for (int i = players[winner].size() - 1, mult = 1; i >= 0; --i) {
		score += players[winner][i] * mult++;
	}
	std::cout << score << std::endl;

	return 0;
}
