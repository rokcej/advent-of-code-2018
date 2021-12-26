import numpy as np

with open("input") as f:
	floor = np.array([[{".":0,">":1,"v":2}[c] for c in l] for l in f.read().splitlines()])

h, w = floor.shape

east = []
south = []
for y in range(h):
	for x in range(w):
		if floor[y, x] == 1:
			east.append([y, x])
		elif floor[y, x] == 2:
			south.append([y, x])

moved = True
step = 0
while moved:
	update_east = []
	for i, (y, x) in enumerate(east):
		x2 = x+1 if x < w-1 else 0
		if floor[y, x2] == 0:
			update_east.append((i, x2))

	for (i, x2) in update_east:
		y, x = east[i]
		floor[y, x] = 0
		floor[y, x2] = 1
		east[i][1] = x2

	update_south = []
	for i, (y, x) in enumerate(south):
		y2 = y+1 if y < h-1 else 0
		if floor[y2, x] == 0:
			update_south.append((i, y2))

	for (i, y2) in update_south:
		y, x = south[i]
		floor[y, x] = 0
		floor[y2, x] = 2
		south[i][0] = y2

	moved = bool(update_east) or bool(update_south)
	step += 1
	
print(step)
