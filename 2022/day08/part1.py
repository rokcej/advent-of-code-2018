import numpy as np

with open("input") as f:
	lines = f.read().splitlines()

w, h = len(lines[0]), len(lines)
trees = np.array([[int(char) for char in line] for line in lines])

visible_sum = 2 * w + 2 * h - 4
for i in range(1, h - 1):
	for j in range(1, w - 1):
		t = trees[i, j]
		if t > trees[:i, j].max() or t > trees[i+1:, j].max() or t > trees[i, :j].max() or t > trees[i, j+1:].max():
			visible_sum += 1
		
print(visible_sum)
