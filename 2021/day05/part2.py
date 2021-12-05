with open("input") as f:
	lines = f.read().splitlines()

def increment(key, dictionary):
	if key in dictionary:
		dictionary[key] += 1
	else:
		dictionary[key] = 1

floor = {}
for line in lines:
	x1, y1, x2, y2 = [int(v) for l in line.split(" -> ") for v in l.split(",")]

	if x1 == x2:
		for i in range(min(y1, y2), max(y1, y2) + 1):
			increment((x1, i), floor)
	elif y1 == y2:
		for i in range(min(x1, x2), max(x1, x2) + 1):
			increment((i, y1), floor)
	else:
		dx = 1 if x2 > x1 else -1
		dy = 1 if y2 > y1 else -1
		for i in range(abs(x2 - x1) + 1):
			increment((x1 + i*dx, y1 + i*dy), floor)

result = sum([count >= 2 for _, count in floor.items()])
print(result)
