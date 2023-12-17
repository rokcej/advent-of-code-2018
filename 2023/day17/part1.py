from queue import PriorityQueue

MAX_FORWARD_STEPS = 3

class Crucible:
	def __init__(self, position, direction, direction_steps):
		self.position = position
		self.direction = direction
		self.direction_steps = direction_steps

	def __lt__(self, other): # Needed because of priority queue
		return False

with open("input") as f:
	lines = f.read().splitlines()

grid = []
for line in lines:
	grid.append(list(map(int, line)))

width, height = len(grid[0]), len(grid)
start_position = (0, 0)
end_position = (width - 1, height - 1)

search = PriorityQueue()
search.put_nowait((0, Crucible(start_position, (+1, 0), 0)))
search.put_nowait((0, Crucible(start_position, (0, +1), 0)))
visited = set()

while not search.empty():
	heat_loss, crucible = search.get_nowait()
	if crucible.position == end_position:
		print(heat_loss)
		break

	visited_key = (crucible.position, crucible.direction, crucible.direction_steps)
	if visited_key in visited:
		continue
	visited.add(visited_key)

	x, y = crucible.position
	dx, dy = crucible.direction

	candidates = []
	if crucible.direction_steps < MAX_FORWARD_STEPS:
		candidates.append(Crucible((x + dx, y + dy), (dx, dy), crucible.direction_steps + 1)) # Forward
	candidates.append(Crucible((x + dy, y - dx), (dy, -dx), 1)) # Left
	candidates.append(Crucible((x - dy, y + dx), (-dy, dx), 1)) # Right

	for candidate in candidates:
		x2, y2 = candidate.position
		if 0 <= x2 < width and 0 <= y2 < height:
			search.put_nowait((heat_loss + grid[y2][x2], candidate))
else:	
	raise Exception("Unable to find solution")
