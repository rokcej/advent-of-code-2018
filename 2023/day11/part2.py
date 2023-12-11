EXPANSION_FACTOR = 1_000_000

with open("input") as f:
	lines = f.read().splitlines()

# Parse input
galaxies = []
for y, line in enumerate(lines):
	for x, char in enumerate(line):
		if char == "#":
			galaxies.append((x, y))

# Expand universe
cols, rows = (set(v) for v in zip(*galaxies))
for i, (x, y) in enumerate(galaxies):
	x_new = x + sum(col not in cols for col in range(x)) * (EXPANSION_FACTOR - 1)
	y_new = y + sum(row not in rows for row in range(y)) * (EXPANSION_FACTOR - 1)
	galaxies[i] = (x_new, y_new)

# Calculate pairwise distances
distance_sum = 0
for i, (x0, y0) in enumerate(galaxies):
	for j, (x1, y1) in enumerate(galaxies[i:]):
		distance_sum += abs(y1 - y0) + abs(x1 - x0)
print(distance_sum)
