from collections import deque

MIRRORS = {
	"/":  lambda dx, dy: (-dy, -dx),
	"\\": lambda dx, dy: (+dy, +dx)
}
SPLITTERS = {
	"-": [(-1, 0), (+1, 0)],
	"|": [(0, -1), (0, +1)]
}

def get_energized_count(start_position, start_direction):
	search = deque([(start_position, start_direction)])
	visited = set()

	while len(search) > 0:
		(x, y), (dx, dy) = search.popleft()
		if not (0 <= x < width and 0 <= y < height):
			continue
		
		if ((x, y), (dx, dy)) in visited:
			continue
		visited.add(((x, y), (dx, dy)))

		tile = grid[y][x]
		if tile in MIRRORS:
			dx2, dy2 = MIRRORS[tile](dx, dy)
			search.append(((x + dx2, y + dy2), (dx2, dy2)))
		elif tile in SPLITTERS:
			if (dx, dy) in SPLITTERS[tile]: # Pass through
				search.append(((x + dx, y + dy), (dx, dy)))
			else: # Split beam
				for dx2, dy2 in SPLITTERS[tile]:
					search.append(((x + dx2, y + dy2), (dx2, dy2)))
		else: # Empty tile
			search.append(((x + dx, y + dy), (dx, dy)))

	energized_positions = set(pos for pos, dir in visited)
	return len(energized_positions)

with open("input") as f:
	lines = f.read().splitlines()

grid = list(map(list, lines))
height = len(grid)
width = len(grid[0])

starting_beams = list()
for x in range(width):
	starting_beams.append(((x, 0), (0, +1)))
	starting_beams.append(((x, height - 1), (0, -1)))
for y in range(height):
	starting_beams.append(((0, y), (+1, 0)))
	starting_beams.append(((width - 1, y), (-1, 0)))

energized_counts = [get_energized_count(pos, dir) for pos, dir in starting_beams]
print(max(energized_counts))
