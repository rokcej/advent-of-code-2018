with open("input", "r") as f:
	input = f.read()

horizontal = 0
depth = 0
for line in input.splitlines():
	fields = line.split(" ")
	dir = fields[0]
	dist = int(fields[1])

	if dir == "forward":
		horizontal += dist
	elif dir == "down":
		depth += dist
	else:
		depth -= dist
	
print(horizontal * depth)
