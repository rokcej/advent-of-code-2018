def is_vertically_mirrored_with_smudge(grid, x):
	error_count = 0
	column_count = min(x + 1, len(grid[0]) - (x + 1))
	for i in range(column_count):
		for y in range(len(grid)):
			error_count += int(grid[y][x - i] != grid[y][x + 1 + i])
			if error_count > 1:
				return False
	return error_count == 1

def is_horizontally_mirrored_with_smudge(grid, y):
	error_count = 0
	row_count = min(y + 1, len(grid) - (y + 1))
	for i in range(row_count):
		for x in range(len(grid[0])):
			error_count += int(grid[y - i][x] != grid[y + 1 + i][x])
			if error_count > 1:
				return False
	return error_count == 1

def get_summary(grid):
	for x in range(len(grid[0]) - 1):
		if is_vertically_mirrored_with_smudge(grid, x):
			return x + 1
	for y in range(len(grid) - 1):
		if is_horizontally_mirrored_with_smudge(grid, y):
			return (y + 1) * 100
	raise Exception("Grid is not mirrored")

with open("input") as f:
	lines = f.read().splitlines()

grids = []
i_grid = 0
while i_grid < len(lines):
	i_empty = i_grid + 1
	while i_empty < len(lines) and bool(lines[i_empty]):
		i_empty += 1
	grids.append([list(line) for line in lines[i_grid:i_empty]])
	i_grid = i_empty + 1

print(sum(map(get_summary, grids)))
