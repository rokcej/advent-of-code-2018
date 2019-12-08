#include <iostream>
#include <vector>

const int W = 25;
const int H = 6;

int main() {
	std::vector<std::vector<int>> layers;

	int minZeros = W * H;
	int minIndex = 0;

	for (int i = 0; std::cin.peek() >= '0' && std::cin.peek() <= '9'; ++i) { // Layers
		layers.emplace_back(W * H);
		int numZeros = 0;
		for (int j = 0; j < W * H; ++j) { // Rows and columns
			int digit = std::cin.get() - '0';
			layers[i][j] = digit;

			if (digit == 0)
				++numZeros;
		}
		if (numZeros < minZeros) {
			minZeros = numZeros;
			minIndex = i;
		}
	}

	int numOnes = 0;
	int numTwos = 0;
	for (int i = 0; i < W * H; ++i) {
		if (layers[minIndex][i] == 1) ++numOnes;
		if (layers[minIndex][i] == 2) ++numTwos;
	}
	std::cout << numOnes * numTwos << std::endl;

	return 0;
}
