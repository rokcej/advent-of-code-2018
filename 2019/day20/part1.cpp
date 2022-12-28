#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>

int main() {
	std::vector<std::string> map;
	for (std::string line; std::getline(std::cin, line);) {
		map.push_back(line);
	}

	// Get outer rectangle bounds
	int x0_out, y0_out;
	for (int y = 0; y < map.size(); ++y) {
		int x = map[y].find('#');
		if (x != std::string::npos) {
			x0_out = x;
			y0_out = y;
			break;
		}
	}
	int w_out = map[y0_out].find(' ', x0_out + 1) - x0_out;
	int h_out = 0;
	while (map[y0_out + (++h_out)][x0_out] != ' '); // Not the cleanest approach

	// Get inner rectangle bounds
	int x0_in, y0_in;
	for (int y = y0_out + 1; y < map.size(); ++y) {
		int x = map[y].find(' ', x0_out + 1);
		if (x != std::string::npos && x < x0_out + w_out - 1) {
			x0_in = x;
			y0_in = y;
			break;
		}
	}
	int w_in = map[y0_in].find('#', x0_in + 1) - x0_in;
	int h_in = 0;
	while (map[y0_in + (++h_in)][x0_in] != '#');


	std::map<std::string, std::vector<std::pair<int, int>>> labels;

	// Get vertical portal positions
	int vertical[2][4] = {{x0_out, x0_out + w_out - 1, y0_out, y0_out + h_out - 1}, {x0_in, x0_in + w_in - 1, y0_in + h_in, y0_in - 1}};
	for (auto [x_start, x_stop, y_up, y_down] : vertical) {
		for (int x = x_start; x <= x_stop; ++x) {
			if (map[y_up][x] == '.') {
				std::string id{map[y_up-2][x], map[y_up-1][x]};
				labels[id].emplace_back(x, y_up);
			}
			if (map[y_down][x] == '.') {
				std::string id{map[y_down+1][x], map[y_down+2][x]};
				labels[id].emplace_back(x, y_down);
			}
		}
	}

	// Get horizontal portal positions
	int horizontal[2][4] = {{y0_out, y0_out + h_out - 1, x0_out, x0_out + w_out - 1}, {y0_in, y0_in + h_in - 1, x0_in + w_in, x0_in - 1}};
	for (auto [y_start, y_stop, x_left, x_right] : horizontal) {
		for (int y = y_start; y <= y_stop; ++y) {
			if (map[y][x_left] == '.') {
				std::string id{map[y][x_left-2], map[y][x_left-1]};
				labels[id].emplace_back(x_left, y);
			}
			if (map[y][x_right] == '.') {
				std::string id{map[y][x_right+1], map[y][x_right+2]};
				labels[id].emplace_back(x_right, y);
			}
		}
	}

	// Connect portals
	int x_start, y_start;
	int x_goal, y_goal;
	std::map<std::pair<int, int>, std::pair<int, int>> portals;
	for (const auto& [id, coords] : labels) {
		if (id == "AA") {
			x_start = coords[0].first;
			y_start = coords[0].second;
		} else if (id == "ZZ") {
			x_goal = coords[0].first;
			y_goal = coords[0].second;
		} else {
			portals[coords[0]] = coords[1];
			portals[coords[1]] = coords[0];
		}
	}

	// BFS baby
	std::queue<std::pair<int, int>> bfs;
	bfs.emplace(x_start, y_start);
	int steps = 0;
	while (!bfs.empty()) {
		for (int count = bfs.size(); count > 0; --count) {
			auto [x, y] = bfs.front();
			bfs.pop();

			if (x == x_goal && y == y_goal) {
				std::cout << steps << std::endl;
				return 0;
			}
			
			// Teleport
			auto it = portals.find(std::make_pair(x, y));
			if (it != portals.end()) {
				auto [x2, y2] = it->second;
				if (map[y2][x2] == '.') {
					map[y2][x2] == '@';
					bfs.emplace(x2, y2);
					continue;
				}
			}

			// Move
			int neighbors[4][2] = {{x-1, y}, {x+1, y}, {x, y-1}, {x, y+1}};
			for (auto [x2, y2] : neighbors) {
				if (map[y2][x2] == '.') {
					map[y2][x2] = '@';
					bfs.emplace(x2, y2);
				}
			}
		}
		++steps;
	}

	std::cout << "No path found" << std::endl;
	
	return 0;
}
