from collections import defaultdict

def is_isolated(y, x, grove):
	for neighbor in [(y+1,x-1), (y+1,x), (y+1,x+1), (y,x-1), (y,x+1), (y-1,x-1), (y-1,x), (y-1,x+1)]:
		if neighbor in grove:
			return False
	return True

def can_move(y, x, y2, x2, grove):
	assert (y == y2 or x == x2) and not (y == y2 and x == x2), "Sadge"
	for pos in ([(y2,x2-1), (y2,x2), (y2,x2+1)] if x == x2 else [(y2-1,x2), (y2,x2), (y2+1,x2)]):
		if pos in grove:
			return False
	return True


with open("input", "r") as f:
	lines = f.read().splitlines()

grove = set()
for y, line in enumerate(lines):
	for x, char in enumerate(line):
		if char == "#":
			grove.add((len(lines) - 1 - y, x)) # Invert the y-axis

dirs = [(+1, 0), (-1, 0), (0, -1), (0, +1)]
i0_dir = 0

for _ in range(10):
	# First half
	proposals = defaultdict(list)
	for y, x in grove:
		if is_isolated(y, x, grove):
			continue

		for i_dir in range(4):
			dy, dx = dirs[(i0_dir + i_dir) % 4]
			y2, x2 = y + dy, x + dx
			if can_move(y, x, y2, x2, grove):
				proposals[(y2, x2)].append((y, x))
				break

	# Second half
	for dest, srcs in proposals.items():
		if len(srcs) != 1:
			continue
		grove.remove(srcs[0])
		grove.add(dest)

	i0_dir += 1

y_min, x_min = next(iter(grove))
y_max, x_max = y_min, x_min
for y, x in grove:
	y_min, x_min = min(y_min, y), min(x_min, x)
	y_max, x_max = max(y_max, y), max(x_max, x)

print((y_max - y_min + 1) * (x_max - x_min + 1) - len(grove))
