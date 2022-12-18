with open("input", "r") as f:
	lines = f.read().splitlines()

lava = set()
for line in lines:
	lava.add(tuple(int(i) for i in line.split(",")))

count = 0
for x, y, z in lava:
	for neighbor in [(x-1,y,z), (x+1,y,z), (x,y-1,z), (x,y+1,z), (x,y,z-1), (x,y,z+1)]:
		if neighbor not in lava:
			count += 1
print(count)
