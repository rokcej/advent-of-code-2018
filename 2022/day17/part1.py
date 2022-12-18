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

with open("input", "r") as f:
	jets = [ord(c)-61 for c in f.read().splitlines()[0]]

rocks = [
	[[1,1,1,1]],               # Horizontal line
	[[0,1,0],[1,1,1],[0,1,0]], # Plus
	[[0,0,1],[0,0,1],[1,1,1]], # Reverse L
	[[1],[1],[1],[1]],         # Vertical line
	[[1,1],[1,1]]              # Square
]

cave = [[0 for _ in range(7)] for _ in range(2022 * 4 + 3)]
height = 0

i_jet = 0
for i_rock in range(2022):
	rock = rocks[i_rock % len(rocks)]
	y, x = height + len(rock) + 2, 2

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

print(height)
