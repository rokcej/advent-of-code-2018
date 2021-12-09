import numpy as np

with open("input") as f:
	heights = np.array([[int(x) for x in l] for l in f.read().splitlines()])

result = 0
for y in range(heights.shape[0]):
	for x in range(heights.shape[1]):
		if ((y == 0 or heights[y,x] < heights[y-1,x]) and
			(x == 0 or heights[y,x] < heights[y,x-1]) and
			(y == heights.shape[0] - 1 or heights[y,x] < heights[y+1,x]) and
			(x == heights.shape[1] - 1 or heights[y,x] < heights[y,x+1])):
			result += heights[y,x] + 1
print(result)
