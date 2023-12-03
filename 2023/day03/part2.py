def get_adjacent_numbers(lines, i, j):
	numbers = []
	i_min, i_max = max(i - 1, 0), min(i + 1, len(lines) - 1)
	j_min, j_max = max(j - 1, 0), min(j + 1, len(lines[i]) - 1)
	for y in range(i_min, i_max + 1):
		x = j_min
		while x <= j_max:
			if not lines[y][x].isdigit():
				x += 1
				continue
			x_min, x_max = x, x
			while x_min - 1 >= 0 and lines[y][x_min - 1].isdigit():
				x_min -= 1
			while x_max + 1 < len(lines[y]) and lines[y][x_max + 1].isdigit():
				x_max += 1
			numbers.append(int(lines[y][x_min : x_max + 1]))
			x = x_max + 2
	return numbers

with open("input") as f:
	lines = f.read().splitlines()
	
gear_ratio_sum = 0
for i in range(len(lines)):
	for j in range(len(lines[i])):
		if lines[i][j] != "*":
			continue
		numbers = get_adjacent_numbers(lines, i, j)
		if len(numbers) == 2:
			gear_ratio_sum += numbers[0] * numbers[1]
print(gear_ratio_sum)
