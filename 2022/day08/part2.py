import numpy as np

with open("input") as f:
	lines = f.read().splitlines()

w, h = len(lines[0]), len(lines)
trees = np.array([[int(char) for char in line] for line in lines])

max_score = 0
for i in range(1, h - 1):
	for j in range(1, w - 1):
		dists = [1, 1, 1, 1]
		while i + dists[0] < h-1 and trees[i, j] > trees[i+dists[0], j]:
			dists[0] += 1
		while i - dists[1] > 0 and trees[i, j] > trees[i-dists[1], j]:
			dists[1] += 1
		while j + dists[2] < w-1 and trees[i, j] > trees[i, j+dists[2]]:
			dists[2] += 1
		while j - dists[3] > 0 and trees[i, j] > trees[i, j-dists[3]]:
			dists[3] += 1
			
		max_score = max(max_score, dists[0] * dists[1] * dists[2] * dists[3])

print(max_score)
