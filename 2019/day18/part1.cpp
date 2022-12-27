/*
Takes about 7 seconds on my i7-6700K

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
	State(int keys, int x, int y, int steps) : keys{keys}, x{x}, y{y}, steps{steps} {}
	int keys;
	int x, y;
	int steps;
};

// Needed for priority queue containing States
bool operator>(const State& lhs, const State& rhs) {
	return lhs.steps >= rhs.steps;
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

	int result = -1;

	std::priority_queue<State, std::vector<State>, std::greater<State>> pqueue;
	pqueue.emplace(0, x0, y0, 0);
	std::set<std::tuple<int, int, int>> seen;
	while (!pqueue.empty()) {
		State state = pqueue.top();
		pqueue.pop();

		if (state.keys == all_keys) {
			result = state.steps;
			break;
		}

		std::tuple<int, int, int> tuple(state.keys, state.x, state.y);
		if (seen.find(tuple) != seen.end()) {
			continue;
		}
		seen.insert(tuple);

		std::vector<Destination> output;
		get_reachable_keys(state.x, state.y, state.keys, map, visited, output);
		for (const Destination& dest : output) {
			pqueue.emplace(add_key(state.keys, dest.key), dest.x, dest.y, state.steps + dest.distance);
		}
	}

	std::cout << result << std::endl;

	return 0;
}
