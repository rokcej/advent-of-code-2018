def is_number_valid(lines, i, j, length):
	i_min, i_max = max(i - 1, 0), min(i + 1, len(lines) - 1)
	j_min, j_max = max(j - 1, 0), min(j + length, len(lines[i]) - 1)
	for y in range(i_min, i_max + 1):
		for x in range(j_min, j_max + 1):
			if not lines[y][x].isdigit() and lines[y][x] != ".":
				return True
	return False

with open("input") as f:
	lines = f.read().splitlines()

number_sum = 0
for i in range(len(lines)):
	j = 0
	while j < len(lines[i]):
		length = 0
		while j + length < len(lines[i]) and lines[i][j + length].isdigit():
			length += 1
		if length > 0 and is_number_valid(lines, i, j, length):
			number_sum += int(lines[i][j : j + length])
		j += max(length, 1)
print(number_sum)
