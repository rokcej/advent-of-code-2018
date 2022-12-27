/*
Takes about 1 minute on my i7-6700K

TODO: We can assume there is only one path between any two points,
so we can precompute distances and gates between each pair of keys
*/

#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <queue>
#include <functional>
#include <set>
#include <tuple>

class Destination {
public:
	Destination(char key, int x, int y, int distance) : key{key}, x{x}, y{y}, distance{distance} {}
	char key;
	int x, y;
	int distance;
};

class State {
public:
	State(int keys, std::pair<int, int> bots[4], int steps) : keys{keys}, steps{steps} {
		for (int i = 0; i < 4; ++i) {
			this->bots[i] = bots[i];
		}
	}
	std::pair<int, int> bots[4];
	int keys;
	int steps;
};

// Needed for priority queue containing States
bool operator>(const State& lhs, const State& rhs) {
	return lhs.steps >= rhs.steps;
}

int get_index(const std::pair<int, int>& xy, const std::vector<std::string>& map) {
	return xy.second * map[0].length() + xy.first;
}

int add_key(int keys, char key) {
	return keys | (1 << (key - 'a'));
}

bool has_key(int keys, char key) {
	return keys & (1 << (key - 'a'));
}

int guid = 1;
void get_reachable_keys(int x, int y, int keys, const std::vector<std::string>& map, std::vector<std::vector<int>>& visited, std::vector<Destination>& output) {
	std::queue<std::pair<int, int>> bfs;
	bfs.emplace(x, y);
	visited[y][x] = guid;

	int distance = 0;
	while (!bfs.empty()) {
		for (int remaining = bfs.size(); remaining > 0; --remaining) {
			auto [x, y] = bfs.front();
			bfs.pop();

			std::pair<int, int> neighbors[4] = { {x-1, y}, {x+1, y}, {x, y-1}, {x, y+1} };
			for (const auto& [x2, y2] : neighbors) {
				char c = map[y2][x2];
				if (visited[y2][x2] == guid || c == '#') {
					continue;
				}

				if (c >= 'a' && c <= 'z') { // Key
					if (!has_key(keys, c)) {
						output.emplace_back(c, x2, y2, distance + 1);
					}
				} else if (c >= 'A' && c <= 'Z') { // Gate
					if (!has_key(keys, c - 'A' + 'a')) {
						continue;
					}
				}

				visited[y2][x2] = guid;
				bfs.emplace(x2, y2);
			}
		}
		++distance;
	}

	++guid;
}

int main() {
	std::vector<std::string> map;
	std::vector<std::vector<int>> visited;
	for (std::string line; std::getline(std::cin, line);) {
		map.push_back(line);
		visited.emplace_back(line.length(), 0);
	}

	int x0, y0;
	int all_keys = 0;
	for (int y = 0; y < map.size(); ++y) {
		for (int x = 0; x < map[y].length(); ++x) {
			char c = map[y][x];
			if (c == '@') {
				x0 = x;
				y0 = y;
			} else if (c >= 'a' && c <= 'z') {
				all_keys = add_key(all_keys, c);
			}
		}
	}

	map[y0-1].replace(x0-1, 3, "@#@");
	map[y0  ].replace(x0-1, 3, "###");
	map[y0+1].replace(x0-1, 3, "@#@");
	std::pair<int, int> bots0[4] = {{x0-1, y0-1}, {x0+1, y0-1}, {x0-1, y0+1}, {x0+1, y0+1}};

	int result = -1;

	std::priority_queue<State, std::vector<State>, std::greater<State>> pqueue;
	pqueue.emplace(0, bots0, 0);
	std::set<std::tuple<int, int, int>> seen;
	while (!pqueue.empty()) {
		State state = pqueue.top();
		pqueue.pop();

		if (state.keys == all_keys) {
			result = state.steps;
			break;
		}

		std::tuple<int, int, int> tuple(
			state.keys, 
			get_index(state.bots[0], map) | (get_index(state.bots[1], map) << 16),
			get_index(state.bots[2], map) | (get_index(state.bots[3], map) << 16)
		);
		if (seen.find(tuple) != seen.end()) {
			continue;
		}
		seen.insert(tuple);

		for (int i = 0; i < 4; ++i) {
			auto [x, y] = state.bots[i];
			std::vector<Destination> output;
			get_reachable_keys(x, y, state.keys, map, visited, output);
			for (const Destination& dest : output) {
				state.bots[i] = std::make_pair(dest.x, dest.y);
				pqueue.emplace(add_key(state.keys, dest.key), state.bots, state.steps + dest.distance);
				state.bots[i] = std::make_pair(x, y);
			}
		}
	}

	std::cout << result << std::endl;

	return 0;
}
