import numpy as np
import queue

with open("input", "r") as f:
	lines = f.read().splitlines()

heightmap = np.zeros((len(lines), len(lines[0])))
for y, line in enumerate(lines):
	for x, char in enumerate(line):
		if char == "S":
			heightmap[y, x] = 0
		elif char == "E":
			end = (y, x)
			heightmap[y, x] = ord("z") - ord("a")
		else:
			heightmap[y, x] = ord(char) - ord("a")

steps = np.full(heightmap.shape, -1)
steps[end] = 0

bfs = queue.Queue()
bfs.put(end)
while (not bfs.empty()):
	y, x = bfs.get()
	for y2, x2 in [(y-1, x), (y+1, x), (y, x-1), (y, x+1)]:
		if not (0 <= y2 < steps.shape[0] and 0 <= x2 < steps.shape[1]):
			continue
		if steps[y2, x2] >= 0 or heightmap[y, x] - heightmap[y2, x2] > 1:
			continue
		steps[y2, x2] = steps[y, x] + 1
		if heightmap[y2, x2] == 0:
			start = (y2, x2)
			bfs.queue.clear()
			break			
		bfs.put((y2, x2))

print(steps[start])
