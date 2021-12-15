import numpy as np
import queue

with open("input") as f:
	scan = np.array([[int(c) for c in l] for l in f.read().splitlines()])

cave = np.tile(scan, (5,5))
th, tw = scan.shape
for ty in range(5):
	for tx in range(5):
		if ty == 0 and tx == 0:
			continue
		cave[ty*th:(ty+1)*th, tx*th:(tx+1)*th] += ty + tx
cave[np.where(cave > 9)] -= 9

h, w = cave.shape
risks = np.full(cave.shape, -1)
frontier = queue.PriorityQueue(cave.size)

frontier.put((0, (0, 0)))
risks[0, 0] = 0
while not frontier.empty():
	risk, (y, x) = frontier.get()
	if y == h-1 and x == w-1:
		break

	def expand(ny, nx):
		new_risk = risk + cave[ny, nx]
		risks[ny, nx] = new_risk
		frontier.put((new_risk, (ny, nx)))

	if y > 0 and risks[y-1, x] == -1:
		expand(y-1, x)
	if y < h-1 and risks[y+1, x] == -1:
		expand(y+1, x)
	if x > 0 and risks[y, x-1] == -1:
		expand(y, x-1)
	if x < w-1 and risks[y, x+1] == -1:
		expand(y, x+1)

print(risks[h-1, w-1])
