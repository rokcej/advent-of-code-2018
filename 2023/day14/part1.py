with open("input") as f:
	lines = f.read().splitlines()

platform = [list(line) for line in lines]
for y in range(len(platform)):
	for x in range(len(platform[0])):
		if platform[y][x] == "O":
			y_new = y
			while y_new > 0 and platform[y_new - 1][x] == ".":
				y_new -= 1
			platform[y][x], platform[y_new][x] = platform[y_new][x], platform[y][x]

total_load = 0
for y in range(len(platform)):
	for x in range(len(platform[0])):
		total_load += int(platform[y][x] == "O") * (len(platform) - y)
print(total_load)
