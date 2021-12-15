import numpy as np
import queue

with open("input") as f:
	cave = np.array([[int(c) for c in l] for l in f.read().splitlines()])

h, w = cave.shape
risks = np.full(cave.shape, -1)
frontier = queue.PriorityQueue(cave.size)

frontier.put((0, (0, 0)))
risks[0, 0] = 0
while not frontier.empty():
	risk, (y, x) = frontier.get()
	if (y, x) == (h-1, w-1):
		break

	for ny, nx in [(y-1,x),(y+1,x),(y,x-1),(y,x+1)]:
		if 0 <= ny < h and 0 <= nx < w:
			if risks[ny, nx] == -1:
				risks[ny, nx] = risk + cave[ny, nx]
				frontier.put((risks[ny, nx], (ny, nx)))

print(risks[h-1, w-1])
