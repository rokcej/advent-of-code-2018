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

def get_loop(pipes, start_position):
	visited = set([start_position])
	bfs = [start_position]
	while bfs:
		position = bfs.pop(0)
		for dx, dy in pipes[(position)]:
			new_position = (position[0] + dx, position[1] + dy)
			if new_position not in visited:
				visited.add(new_position)
				bfs.append(new_position)
	return visited

def get_enclosed_count(pipes, loop):
	x_values, y_values = zip(*loop)
	x_min, x_max = min(x_values), max(x_values)
	y_min, y_max = min(y_values), max(y_values)

	# Cast a ray from every point within the loop bounding box and count intersections with the loop
	# If the intersection count is odd, the point is enclosed by the loop
	# Make sure not to count tangents as intersections
	enclosed_count = 0
	for x in range(x_min + 1, x_max):
		for y in range(y_min + 1, y_max):
			if (x, y) in loop:
				continue
			intersection_count = 0
			overlap_dy_sum = 0
			for x2 in range(x + 1, x_max):
				if (x2, y) in loop:
					overlap_dy_sum += sum(dy for dx, dy in pipes[(x2, y)])
					intersection_count += int(overlap_dy_sum == 0)
					overlap_dy_sum = (overlap_dy_sum % 2) * (-1 if overlap_dy_sum < 0 else +1) # Signed mod
			enclosed_count += intersection_count % 2
	return enclosed_count

with open("input") as f:
	lines = f.read().splitlines()

pipes, start_position = parse_input(lines)
loop = get_loop(pipes, start_position)
print(get_enclosed_count(pipes, loop))
