import numpy as np

with open("input") as f:
	octopi = np.array([[int(c) for c in l] for l in f.read().splitlines()])
h, w = octopi.shape

step = 1
while True:
	octopi += 1
	bfs = list(zip(*np.where(octopi == 10)))
	while len(bfs) > 0:
		y, x = bfs.pop()
		y0, x0, y1, x1 = max(y-1, 0), max(x-1, 0), min(y+2, h), min(x+2, w)
		for ny in range(y0, y1):
			for nx in range(x0, x1):
				if not (nx == x and ny == y):
					octopi[ny,nx] += 1
					if octopi[ny,nx] == 10:
						bfs.append((ny,nx))
	if np.count_nonzero(octopi > 9) == octopi.size: # Faster than np.sum
		break
	octopi[octopi > 9] = 0
	step += 1
print(step)
