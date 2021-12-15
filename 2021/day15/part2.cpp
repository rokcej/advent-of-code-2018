#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <string>
#include <chrono>
#include <tuple>
#include <iomanip>

class Element {
public:
	int risk, y, x;
	Element (int risk, int y, int x) {
		this->risk = risk;
		this->y = y;
		this->x = x;
	}
	bool operator<(const Element& rhs) const {
		return this->risk > rhs.risk; // Intentionally reversed
	}
};

int main() {
	auto t0 = std::chrono::high_resolution_clock::now();

	std::vector<std::string> lines;
	std::ifstream input("input");
	for (std::string line; input >> line;)
		lines.push_back(line);

	int th = lines.size();
	int tw = lines[0].size();
	int **scan = new int*[th];
	for (int i = 0; i < th; ++i) {
		scan[i] = new int[tw];
		for (int j = 0; j < tw; ++j)
			scan[i][j] = lines[i][j] - '0';
	}

	int h = 5 * th;
	int w = 5 * tw;

	int **cave = new int*[h];
	int **risks = new int*[h];
	for (int i = 0; i < h; ++i) {
		int ti = i / th;
		int ty = i % th;
		cave[i] = new int[w];
		risks[i] = new int[w];
		for (int j = 0; j < w; ++j) {
			int tj = j / tw;
			int tx = j % tw;
			cave[i][j] = scan[ty][tx] + ti + tj;
			if (cave[i][j] > 9)
				cave[i][j] -= 9;
			risks[i][j] = -1;
		}
	}

	std::priority_queue<Element> frontier;
	frontier.push(Element(0, 0, 0));
	while (!frontier.empty()) {
		Element el = frontier.top();
		frontier.pop();
		if (el.y == h-1 && el.x == w-1)
			break;

		auto expand = [&](int ny, int nx) {
			int new_risk = el.risk + cave[ny][nx];
			risks[ny][nx] = new_risk;
			frontier.push(Element(new_risk, ny, nx));
		};

		if (el.y > 0 && risks[el.y-1][el.x] == -1)
			expand(el.y-1, el.x);
		if (el.y < h-1 && risks[el.y+1][el.x] == -1)
			expand(el.y+1, el.x);
		if (el.x > 0 && risks[el.y][el.x-1] == -1)
			expand(el.y, el.x-1);
		if (el.x < w-1 && risks[el.y][el.x+1] == -1)
			expand(el.y, el.x+1);
	}
	
	auto t1 = std::chrono::high_resolution_clock::now();
	float dt = std::chrono::duration<float>(t1 - t0).count();

	std::cout << "Part 2" << std::endl;
	std::cout << risks[h-1][w-1] << std::endl;
	std::cout << "Time: " << std::setprecision(4) << dt << "s" << std::endl;

	return 0;
}
