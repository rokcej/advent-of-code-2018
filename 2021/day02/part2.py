with open("input", "r") as f:
	input = f.read()

horizontal = 0
depth = 0
aim = 0
for line in input.splitlines():
	fields = line.split(" ")
	dir = fields[0]
	dist = int(fields[1])

	if dir == "forward":
		horizontal += dist
		depth += aim * dist
	elif dir == "down":
		aim += dist
	else:
		aim -= dist
	
print(horizontal * depth)
