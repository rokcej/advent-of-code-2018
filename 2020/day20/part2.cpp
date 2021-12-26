#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <array>
#include <utility>

// Equal
bool eq(const std::string& a, const std::string& b) {
	return a.compare(b) == 0;
}
// Equal in reverse
bool eqr(const std::string& a, const std::string& b) {
	int len = a.length();
	for (int i = 0; i < len; ++i) {
		if (a[i] != b[len - 1 - i])
			return false;
	}
	return true;
}

class Tile {
public:
	std::vector<std::string> data;
	int neighbors[4] = { -1, -1, -1, -1 }; // N W S E
	int matches = 0;

	std::vector<std::string> get_edges() {
		std::vector<std::string> edges(4);
		edges[0] = data.front();
		edges[2] = data.back();
		for (int i = 0; i < data.size(); ++i) {
			edges[1] += data[i].front();
			edges[3] += data[i].back();
		}
		return edges;
	}

	void rotate() { // Rotate 90 degrees CCW
		int h = data.size();
		int w = data[0].size();
		if (h != w) {
			std::cout << "ERR " << h << "!=" << w << std::endl;
			return;
		}
		int d = data.size();
		std::vector<std::string> rotated(data);
		for (int i = 0; i < d; ++i) {
			for (int j = 0; j < d; ++j) {
				rotated[i][j] = data[j][d-1-i];
			}
		}
		data.swap(rotated);
		// Rotate neighbor references
		int tmp = neighbors[3];
		for (int i = 3; i >= 1; --i) {
			neighbors[i] = neighbors[i-1];
		}
		neighbors[0] = tmp;
	}

	void flip_x() { // Flip the x coordinate
		for (int i = 0; i < data.size(); ++i) {
			for (int j = 0; j < data[i].size() / 2; ++j) {
				int j2 = data[i].size() - 1 - j;
				int tmp = data[i][j];
				data[i][j] = data[i][j2];
				data[i][j2] = tmp;
			}
		}
		// Flip neighbor references
		int tmp = neighbors[1];
		neighbors[1] = neighbors[3];
		neighbors[3] = tmp;
	}
};

int main() {
	std::unordered_map<int, Tile> tiles;

	// Read input
	for (std::string line; std::getline(std::cin, line);) {
		int id = std::stoi(line.substr(5, line.length() - 6));
		while (std::getline(std::cin, line) && !line.empty()) {
			tiles[id].data.push_back(line);
		}
	}

	// Find all neighborus for each tile
	int corner = -1;
	for (auto& el1 : tiles) {
		int id1 = el1.first;
		int count = 0;
		auto edges1 = el1.second.get_edges();
		for (auto& el2 : tiles) {
			int id2 = el2.first;
			if (id1 == id2)
				continue;
			auto edges2 = el2.second.get_edges();
			for (int i = 0; i < 4; ++i) {
				for (int j = 0; j < 4; ++j) {
					if (eq(edges1[i], edges2[j]) || eqr(edges1[i], edges2[j])) {
						++count;
						el1.second.neighbors[i] = id2;
						el2.second.neighbors[j] = id1;
						break;
					}
				}
			}
		}
		el1.second.matches = count;
		// Store corner tile
		if (corner == -1 && count == 2) {
			corner = id1;
		}
	}

	// Rotate corner tile so it represents the upper left corner
	while (!(tiles[corner].neighbors[0] == -1 && tiles[corner].neighbors[1] == -1)) {
		tiles[corner].rotate();
	}

	// Start putting tiles together in correct orientation
	std::vector<std::vector<int>> puzzle;
	puzzle.push_back({corner});
	// First row
	for (int id = corner; tiles[id].neighbors[3] != -1;) {
		int id2 = tiles[id].neighbors[3];
		puzzle[0].push_back(id2);
		int iso = 0;
		while (!(tiles[id2].neighbors[0] == -1 && tiles[id2].neighbors[1] == id)) {
			if (iso++ == 3) {
				tiles[id2].flip_x();
			} else {
				tiles[id2].rotate();
			}
		}
		id = id2;
	}
	// First column
	for (int id = corner; tiles[id].neighbors[2] != -1;) {
		int id2 = tiles[id].neighbors[2];
		puzzle.push_back({id2});
		int iso = 0;
		while (!(tiles[id2].neighbors[1] == -1 && tiles[id2].neighbors[0] == id)) {
			if (iso++ == 3) {
				tiles[id2].flip_x();
			} else {
				tiles[id2].rotate();
			}
		}
		id = id2;
	}
	// Rest of the image
	for (int i = 1; i < puzzle.size(); ++i) {
		for (int j = 1; j < puzzle[0].size(); ++j) {
			int up = puzzle[i-1][j];
			int left = puzzle[i][j-1];
			int id = tiles[up].neighbors[2];
			puzzle[i].push_back(id);
			int iso = 0;
			while (!(tiles[id].neighbors[0] == up && tiles[id].neighbors[1] == left)) {
				if (iso++ == 3) {
					tiles[id].flip_x();
				} else {
					tiles[id].rotate();
				}
			}

		}
	}

	// Reconstruct full image
	int th = tiles[puzzle[0][0]].data.size(); // Tile height
	int tw = tiles[puzzle[0][0]].data[0].size(); // Tile width
	int h = puzzle.size() * (th - 2);
	int w = puzzle[0].size() * (tw - 2);

	Tile image;
	for (int i = 0; i < h; ++i)
		image.data.push_back("");

	for (int ti = 0; ti < puzzle.size(); ++ti) {
		for (int tj = 0; tj < puzzle[0].size(); ++tj) {
			int id = puzzle[ti][tj];
			for (int i = 0; i < th - 2; ++i) {
				image.data[ti * (th-2) + i] += tiles[id].data[i+1].substr(1, tw-2);
			}
		}
	}
	
	// Store pattern coordinates
	std::vector<std::string> pattern = {
		"                  # ",
		"#    ##    ##    ###",
		" #  #  #  #  #  #   "
	};
	int ph = pattern.size();
	int pw = pattern[0].size();
	std::vector<std::pair<int, int>> coords;
	for (int i = 0; i < ph; ++i) {
		for (int j = 0; j < pw; ++j) {
			if (pattern[i][j] == '#') {
				coords.push_back(std::make_pair(i, j));
			}
		}
	}

	// Find image orientation with pattern
	int iso = 0;
	while (true) {
		bool oriented = false;
		for (int i = 0; i < h - ph + 1; ++i) {
			for (int j = 0; j < w - pw + 1; ++j) {
				int matches = true;
				for (auto coord : coords) {
					int y = coord.first;
					int x = coord.second;
					if (image.data[i+y][j+x] == '.') {
						matches = false;
						break;
					}
				}
				if (matches) {
					for (auto coord : coords) {
						int y = coord.first;
						int x = coord.second;
						image.data[i+y][j+x] = 'O';
					}
					oriented = true;
				}
			}
		}

		if (oriented) {
			break;
		}
		
		if (iso++ == 3) {
			image.flip_x();
		} else {
			image.rotate();
		}
	}

	// Calculate result
	int result = 0;
	for (int i = 0; i < h; ++i) {
		for (int j = 0; j < w; ++j) {
			if (image.data[i][j] == '#') {
				++result;
			}
		}
	};
	std::cout << result << std::endl;

	return 0;
}
