import numpy as np

with open("input") as f:
	octopi = np.array([[int(c) for c in l] for l in f.read().splitlines()])
h, w = octopi.shape

step = 1
while True:
	for y0 in range(h):
		for x0 in range(w):
			octopi[y0,x0] += 1
			if octopi[y0,x0] != 10:
				continue
			bfs = [(y0,x0)]
			while len(bfs) > 0:
				y, x = bfs.pop()
				for ny in range(max(y-1, 0), min(y+2, h)):
					for nx in range(max(x-1, 0), min(x+2, w)):
						if not (nx == x and ny == y):
							octopi[ny,nx] += 1
							if octopi[ny,nx] == 10:
								bfs.append((ny,nx))
	if np.count_nonzero(octopi > 9) == octopi.size: # Faster than np.sum
		break
	octopi[octopi > 9] = 0
	step += 1

print(step)
