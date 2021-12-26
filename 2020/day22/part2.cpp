#include <iostream>
#include <string>
#include <deque>
#include <set>
#include <algorithm>
#include <utility>

int rec(std::deque<int> players[2]) {
	int maxima[2];
	for (int i = 0; i < 2; ++i) {
		maxima[i] = *std::max_element(players[i].begin(), players[i].end());
	}
	if (maxima[0] > maxima[1] && maxima[0] > players[0].size() + players[1].size()) {
		return 0;
	}

	std::set<std::pair<std::deque<int>, std::deque<int>>> seen;

	while (!players[0].empty() && !players[1].empty()) {
		auto key = std::make_pair(std::deque<int>(players[0]), std::deque<int>(players[1]));
		if (seen.find(key) != seen.end()) {
			return 0;
		}
		seen.insert(key);

		int cards[2];
		bool can_recurse = true;
		for (int i = 0; i < 2; ++i) {
			cards[i] = players[i].front();
			players[i].pop_front();
			can_recurse = can_recurse && cards[i] <= players[i].size();
		}

		int i_winner = cards[0] < cards[1];
		if (can_recurse) {
			std::deque<int> players_rec[2];
			for (int i = 0; i < 2; ++i) {
				for (int j = 0; j < cards[i]; ++j) {
					players_rec[i].push_back(players[i][j]);
				}
			}
			i_winner = rec(players_rec);
		}

		players[i_winner].push_back(cards[i_winner]);
		players[i_winner].push_back(cards[1-i_winner]);
	}
	return players[0].empty();
}

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

	int winner = rec(players);
	int score = 0;
	for (int i = players[winner].size() - 1, mult = 1; i >= 0; --i) {
		score += players[winner][i] * mult++;
	}
	std::cout << score << std::endl;

	return 0;
}
