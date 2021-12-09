import numpy as np

def bfs(heights, basins, id, y0, x0):
	search = [(y0,x0)]
	size = 0
	while len(search) != 0:
		y, x = search.pop(0)
		if basins[y,x] == 0:
			basins[y,x] = id
			size += 1
			neighbors = []
			if y > 0: neighbors.append((y-1,x))
			if x > 0: neighbors.append((y,x-1))
			if y < heights.shape[0]-1: neighbors.append((y+1,x))
			if x < heights.shape[1]-1: neighbors.append((y,x+1))
			for ny, nx in neighbors:
				if heights[ny,nx] < 9 and heights[ny,nx] > heights[y,x]:
					search.append((ny,nx))
	return size

with open("input") as f:
	heights = np.array([[int(x) for x in l] for l in f.read().splitlines()])

basins = np.zeros(heights.shape)
sizes = []
id = 0
for y in range(heights.shape[0]):
	for x in range(heights.shape[1]):
		if ((y == 0 or heights[y,x] < heights[y-1,x]) and
			(x == 0 or heights[y,x] < heights[y,x-1]) and
			(y == heights.shape[0] - 1 or heights[y,x] < heights[y+1,x]) and
			(x == heights.shape[1] - 1 or heights[y,x] < heights[y,x+1])):
			id += 1
			sizes.append(bfs(heights, basins, id, y, x))

result = 1
for size in sorted(sizes)[-3:]: result *= size
print(result)
