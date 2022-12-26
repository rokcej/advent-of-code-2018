"""
+----------------------+         +------------+
|                      A         B            |   
|                 +---------+---------+       |
|                 |    >    |    >    |       |
|  +------------N | v       |       v | C--+  |
|  |              |         |    >    |    |  |
|  |              +---------+---------+    |  |
|  |              |         |    D         |  |
|  |         +--M | v     v | E--+         |  |
|  |         L    |         |              |  |
|  |    +---------+---------+              |  |
|  |    |    >    |         |              |  |
|  +--K | ^       |       ^ | F------------+  |
|       |         |    >    |                 |
|       +---------+---------+                 |
|       |         |    G                      |
+-----J | v     v | H--+                      |
        |    >    |                           |
        +---------+                           |
             I                                |
             +--------------------------------+

The solution is hard-coded to only work for inputs of this shape.
"""

RIGHT, DOWN, LEFT, UP = 0, 1, 2, 3
DIRS = [(0, +1), (+1, 0), (0, -1), (-1, 0)]

def get_path(line: str) -> list:
	path = []
	i = 0
	while i < len(line):
		if line[i].isalpha():
			path.append(line[i])
			i += 1
		else:
			j = i + 1
			while j < len(line) and line[j].isnumeric():
				j += 1
			path.append(int(line[i:j]))
			i = j
	return path

def wrap(y, x, dir):
	# Lord forgive me for what I'm about to do
	if y == -1 and 50 <= x < 100:                   # A -> J
		return 150 + x - 50, 0, RIGHT
	if y == -1 and 100 <= x < 150:                  # B -> I
		return 199, x - 100, UP
	if 0 <= y < 50 and x == 150:                    # C -> F
		return 149 - y, 99, LEFT
	if y == 50 and 100 <= x < 150 and dir == DOWN:  # D -> E
		return 50 + x - 100, 99, LEFT
	if 50 <= y < 100 and x == 100 and dir == RIGHT: # E -> D
		return 49, 100 + y - 50, UP
	if 100 <= y < 150 and x == 100:                 # F -> C
		return 149 - y, 149, LEFT
	if y == 150 and 50 <= x < 100 and dir == DOWN:  # G -> H
		return 150 + x - 50, 49, LEFT
	if 150 <= y < 200 and x == 50 and dir == RIGHT: # H -> G
		return 149, 50 + y - 150, UP
	if y == 200 and 0 <= x < 50:                    # I -> B
		return 0, 100 + x, DOWN
	if 150 <= y < 200 and x == -1:                  # J -> A
		return 0, 50 + y - 150, DOWN
	if 100 <= y < 150 and x == -1:                  # K -> N
		return 149 - y, 50, RIGHT
	if y == 99 and 0 <= x < 50 and dir == UP:       # L -> M
		return 50 + x, 50, RIGHT
	if 50 <= y < 100 and x == 49 and dir == LEFT:   # M -> L
		return 100, y - 50, DOWN
	if 0 <= y < 50 and x == 49:                     # N -> K
		return 149 - y, 0, RIGHT
	
	return y, x, dir


with open("input", "r") as f:
	lines = f.read().splitlines()

i_empty = lines.index("")
board = lines[:i_empty]
path = get_path(lines[i_empty+1])

y = 0
x = board[0].find(".")
dir = RIGHT

for element in path:
	# Change direction
	if element == "R":
		dir = (dir + 1) % 4
		continue
	if element == "L":
		dir = (dir + 3) % 4
		continue

	# Move
	distance = element
	for _ in range(distance):
		dy, dx = DIRS[dir]
		y2, x2, dir2 = wrap(y + dy, x + dx, dir)
		if board[y2][x2] == "#":
			break
		y, x, dir = y2, x2, dir2

print(1000 * (y + 1) + 4 * (x + 1) + dir)
