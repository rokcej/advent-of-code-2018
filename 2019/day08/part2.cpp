#include <iostream>
#include <vector>

const int W = 25;
const int H = 6;

int main() {
	std::vector<std::vector<int>> layers;

	for (int i = 0; std::cin.peek() >= '0' && std::cin.peek() <= '9'; ++i) { // Layers
		layers.emplace_back(W * H);
		for (int j = 0; j < W * H; ++j) { // Rows and columns
			int digit = std::cin.get() - '0';
			layers[i][j] = digit;
		}
	}

	for (int i = 0; i < H; ++i) { // Rows
		for (int j = 0; j < W; ++j) { // Columns
			int idx = i * W + j;
			int pixel = 2;
			for (int k = 0; k < layers.size(); ++k) {
				pixel = layers[k][idx];
				if (pixel != 2)
					break;
			}
			std::cout << (char) (pixel ? '#' : ' ');
		}
		std::cout << std::endl;
	}

	return 0;
}
