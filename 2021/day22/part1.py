import numpy as np

with open("input") as f:
	lines = f.read().splitlines()

steps = []
for line in lines:
	command, coords = line.split()
	val = int(command == "on")
	cuboid = [[int(c)+50 for c in d.split("=")[1].split("..")] for d in coords.split(",")]
	steps.append((val, cuboid))

reactor = np.zeros((101, 101, 101), dtype=np.int32)
for val, cuboid in steps:
	valid = True
	for i in range(3):
		if cuboid[i][0] > 100 or cuboid[i][1] < 0:
			invalid = False
			break
		else:
			cuboid[i][0] = max(cuboid[i][0], 0)
			cuboid[i][1] = min(cuboid[i][1], 100)
	if not valid:
		break

	[x0,x1],[y0,y1],[z0,z1] = cuboid
	reactor[x0:x1+1, y0:y1+1, z0:z1+1] = val

print(np.sum(reactor))
