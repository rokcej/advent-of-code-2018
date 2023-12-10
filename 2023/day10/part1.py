PIPE_DIRECTIONS = {
	"|": [(0, -1), (0, +1)],
	"-": [(-1, 0), (+1, 0)],
	"L": [(0, -1), (+1, 0)],
	"J": [(0, -1), (-1, 0)],
	"7": [(-1, 0), (0, +1)],
	"F": [(+1, 0), (0, +1)]
}

def parse_input(lines):
	pipes = dict()
	start_position = None
	for y, line in enumerate(lines):
		for x, char in enumerate(line):
			if char == "S":
				start_position = (x, y)
				pipes[(x, y)] = []
			elif char in PIPE_DIRECTIONS:
				pipes[(x, y)] = PIPE_DIRECTIONS[char]
	
	# Connect S to neighboring pipes	
	for dx, dy in [(-1, 0), (+1, 0), (0, -1), (0, +1)]:
		position = (start_position[0] + dx, start_position[1] + dy)
		if position in pipes:
			if (-dx, -dy) in pipes[position]:
				pipes[start_position].append((dx, dy))
	return pipes, start_position

def get_max_steps(pipes, start_position):
	steps = 0
	visited = set([start_position])
	bfs = [(start_position, steps)]
	while bfs:
		position, steps = bfs.pop(0)
		for dx, dy in pipes[(position)]:
			new_position = (position[0] + dx, position[1] + dy)
			if new_position not in visited:
				visited.add(new_position)
				bfs.append((new_position, steps + 1))
	return steps

with open("input") as f:
	lines = f.read().splitlines()

pipes, start_position = parse_input(lines)
print(get_max_steps(pipes, start_position))
