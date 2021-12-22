import numpy as np

with open("input") as f:
	lines = f.read().splitlines()

steps = []
for line in lines:
	command, coords = line.split()
	val = int(command == "on")
	cuboid = [[int(c)+50 for c in d.split("=")[1].split("..")] for d in coords.split(",")]
	steps.append((val, cuboid))

def get_intersection(a, b):
	inter = []
	for i in range(3):
		c0 = max(a[i][0], b[i][0])
		c1 = min(a[i][1], b[i][1])
		if c0 > c1:
			return None
		inter.append([c0, c1])
	return inter

added = []
for val, cuboid in steps:
	inters = []
	for val2, cuboid2 in added:
		inter = get_intersection(cuboid, cuboid2)
		if inter is not None:
			val_inter = 1 - val2
			inters.append([val_inter, inter])
	added += inters
	if val == 1:
		added += [[val, cuboid]]
	
result = 0
for val, cuboid in added:
	volume = 1
	for i in range(3):
		volume *= (cuboid[i][1] - cuboid[i][0] + 1)
	result += volume if val == 1 else -volume
print(result)
