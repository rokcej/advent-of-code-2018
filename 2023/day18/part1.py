DIRECTIONS = {"R": (+1, 0), "D": (0, +1), "L": (-1, 0), "U": (0, -1)}

with open("input") as f:
	lines = f.read().splitlines()

instructions = []
for line in lines:
	direction_str, distance_str, _ = line.split()
	direction = DIRECTIONS[direction_str]
	distance = int(distance_str)
	instructions.append((direction, distance))

position = (0, 0)
holes = set([position])
for (dx, dy), distance in instructions:
	for _ in range(distance):
		position = (position[0] + dx, position[1] + dy)
		holes.add(position)

x_values, y_values = zip(*holes)
x_min, x_max = min(x_values), max(x_values)
y_min, y_max = min(y_values), max(y_values)

outside = set()
search = [(x_min - 1, y_min - 1)]
while len(search) > 0:
	x, y = search.pop() # DFS
	outside.add((x, y))
	for x2, y2 in [(x, y-1), (x, y+1), (x-1, y), (x+1, y)]:
		is_valid = (x_min-1 <= x2 <= x_max+1) and (y_min-1 <= y2 <= y_max+1)
		if not is_valid or (x2, y2) in outside or (x2, y2) in holes:
			continue
		search.append((x2, y2))
inside_count = (x_max - x_min + 3) * (y_max - y_min + 3) - len(outside)
print(inside_count)
