"""
Simulate rocks falling until the tower top becomes flat for the first time.
Continue until the tower top becomes flat again (rock shape and jet direction indices must be the same as the first time).
Afterwards, the simulation becomes repetitive, so the height of the tower for any number of rocks can be calculated.
"""

def can_place(y, x, rock, cave):
	if x < 0 or x + len(rock[0]) - 1 >= len(cave[0]):
		return False
	if y - len(rock) + 1 < 0:
		return False
	for i in range(len(rock)):
		for j in range(len(rock[0])):
			if rock[i][j] and cave[y-i][x+j]:
				return False
	return True

def place(y, x, rock, cave):
	for i in range(len(rock)):
		for j in range(len(rock[0])):
			if rock[i][j]:
				cave[y-i][x+j] = 1

def is_flat(height, cave):
	for j in range(len(cave[0])):
		if not cave[height-1][j]:
			return False
	return True

with open("input", "r") as f:
	jets = [ord(c)-61 for c in f.read().splitlines()[0]]

rocks = [
	[[1,1,1,1]],               # Horizontal line
	[[0,1,0],[1,1,1],[0,1,0]], # Plus
	[[0,0,1],[0,0,1],[1,1,1]], # Reverse L
	[[1],[1],[1],[1]],         # Vertical line
	[[1,1],[1,1]]              # Square
]

cave = []
height = 0
heights = [height]

cycle_begin = None
cycle_end = None
cycle_indices = None

i_jet = 0
i_rock = 0
while cycle_end is None:
	rock = rocks[i_rock % len(rocks)]
	y, x = height + len(rock) + 2, 2
	if y >= len(cave):
		cave.extend([[0 for _ in range(7)] for _ in range(y - height + 1)])

	while True:
		# Push sideways
		dx = jets[i_jet % len(jets)]
		i_jet += 1
		if can_place(y, x + dx, rock, cave):
			x += dx
		# Fall down
		if can_place(y - 1, x, rock, cave):
			y -= 1
		else:
			break
	
	place(y, x, rock, cave)
	height = max(height, y + 1)
	heights.append(height)

	if is_flat(height, cave):
		if cycle_begin is None:
			cycle_begin = (i_rock, height)
			cycle_indices = (i_rock % len(rocks), i_jet % len(jets))
		elif (i_rock % len(rocks)) == cycle_indices[0] and (i_jet % len(jets)) == cycle_indices[1]:
			cycle_end = (i_rock, height)

	i_rock += 1

offset = cycle_begin[0] + 1                             # Number of rocks before the first cycle
cycle_duration = cycle_end[0] - cycle_begin[0]          # Number of rocks within each cycle
cycle_height = cycle_end[1] - cycle_begin[1]            # Tower height gained during each cycle
num_cycles = (1000000000000 - offset) // cycle_duration # Number of completed cycles
remainder = (1000000000000 - offset) % cycle_duration   # Position within the last cycle

print(num_cycles * cycle_height + heights[offset + remainder])
