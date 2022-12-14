import numpy as np

with open("input", "r") as f:
	lines = f.read().splitlines()

y0, x0 = 0, 500
y_min, y_max = y0, y0
x_min, x_max = x0, x0

paths = []
for line in lines:
	paths.append([])
	for point in line.split(" -> "):
		x, y = tuple(map(int, point.split(",")))
		y_min, y_max = min(y_min, y), max(y_max, y)
		x_min, x_max = min(x_min, x), max(x_max, x)
		paths[-1].append((y, x))

# Add infinite floor
y_max += 2
# Adjust for min and max x values that might get indexed
x_min = min(x_min - 1, x0 - y_max)
x_max = max(x_max + 1, x0 + y_max)

cave = np.zeros((y_max-y_min+1, x_max-x_min+1), dtype=np.int32)
for path in paths:
	for i in range(len(path) - 1):
		i0, i1 = sorted([path[i][0], path[i+1][0]])
		j0, j1 = sorted([path[i][1], path[i+1][1]])
		cave[i0:i1+1, j0-x_min:j1+1-x_min] = 1

count = 0
while True:
	y, x = y0, x0
	while y < y_max - 1:
		if cave[y+1, x-x_min] == 0:
			y, x = y+1, x
		elif cave[y+1, x-1-x_min] == 0:
			y, x = y+1, x-1
		elif cave[y+1, x+1-x_min] == 0:
			y, x = y+1, x+1
		else:
			break
		
	cave[y, x-x_min] = 2
	count += 1
	if (y, x) == (y0, x0):
		break
print(count)
