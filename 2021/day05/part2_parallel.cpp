/**
 * DO NOT USE
 * This is slower than the single-threaded version
 */

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <utility>
#include <algorithm>
#include <chrono>
#include <thread>
#include <mutex>
#include <vector>
#include <sstream>

#define HASH(x,y) (((y) << 16) | (x))
#define NUM_THREADS 8

std::unordered_map<int, int> g_map;
std::mutex g_map_mutex;
std::vector<std::string> lines;

void worker(int id) {
	std::unordered_map<int, int> map;

	int i0 = (((lines.size() - 1) / NUM_THREADS) + 1) * id;
	int i1 = std::min((((lines.size() - 1) / NUM_THREADS) + 1) * (id + 1), lines.size());

	for (int i = i0; i < i1; ++i) {
		int x1 = std::stoi(lines[i]);
		int split = lines[i].find(",");
		int y1 = std::stoi(&lines[i][split+1]);

		split = lines[i].find(" -> ", split);
		int x2 = std::stoi(&lines[i][split+4]);
		split = lines[i].find(",", split);
		int y2 = std::stoi(&lines[i][split+1]);

		if (x1 == x2) {
			for (int y = std::min(y1,y2); y <= std::max(y1,y2); ++y) {
				++map[HASH(x1, y)];
			}
		} else if (y1 == y2) {
			for (int x = std::min(x1,x2); x <= std::max(x1,x2); ++x) {
				++map[HASH(x, y1)];
			}
		} else {
			int dx = x2 > x1 ? 1 : -1;
			int dy = y2 > y1 ? 1 : -1;
			for (int i = 0; i <= std::abs(x2 - x1); ++i) {
				++map[HASH(x1 + i*dx, y1 + i*dy)];
			}
		}
	}

	std::unique_lock<std::mutex> lock(g_map_mutex);
	for (auto it = map.begin(); it != map.end(); ++it) {
		g_map[it->first] += it->second;
	}
	lock.unlock();
}

int solve() {
	std::ifstream in("input");

	lines.reserve(500);
	std::string line;
	for (int i = 0; std::getline(in, line); ++i) {
		lines.push_back(line);
	}
	in.close();

	std::vector<std::thread> threads(NUM_THREADS);

	for (int t = 0; t < NUM_THREADS; ++t) {
		threads[t] = std::thread(worker, t);
	}
	for (int t = 0; t < NUM_THREADS; ++t) {
		threads[t].join();
	}

	int result = 0;
	for (auto it = g_map.begin(); it != g_map.end(); ++it) {
		if (it->second >= 2) {
			++result;
		}
	}

	return result;
}

int main() {
	auto time_start = std::chrono::steady_clock::now();
	
	std::cout<< solve() << std::endl;

	auto time_end = std::chrono::steady_clock::now();
	double time = std::chrono::duration<double>(time_end - time_start).count();
	std::cout << time << std::endl;
}
