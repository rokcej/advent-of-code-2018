"""
First, compute sections that each sensor covers on y=2000000 (sections should not inclue beacons).
Then, join sections that are intersecting.
Finally, sum the lengths of all remaining sections.
"""

def get_distance(a, b):
	return abs(a[0] - b[0]) + abs(a[1] - b[1])

with open("input", "r") as f:
	lines = f.read().splitlines()

y_check = 2000000
sections = list()

for line in lines:
	tokens = line.split()
	sensor = int(tokens[2][2:-1]), int(tokens[3][2:-1])
	beacon = int(tokens[-2][2:-1]), int(tokens[-1][2:])

	max_dist = get_distance(sensor, beacon)
	dist = get_distance(sensor, (sensor[0], y_check))

	if dist <= max_dist:
		remaining = max_dist - dist
		x0, x1 = sensor[0] - remaining, sensor[0] + remaining

		if beacon[1] == y_check and x0 <= beacon[0] <= x1:
			if beacon[0] == x0:
				sections.append((x0+1, x1))
			elif beacon[0] == x1:
				sections.append((x0, x1-1))
			else:
				sections.extend([(x0, beacon[0]-1), (beacon[0]+1, x1)])
		else:
			sections.append((x0, x1))

sections.sort(key=(lambda s: s[0]))
for i in range(len(sections)-2, -1, -1):
	while i+1 < len(sections) and sections[i][1] >= sections[i+1][0]:
		sections[i] = (sections[i][0], max(sections[i][1], sections[i+1][1]))
		sections.pop(i+1)

print(sum([x1 - x0 + 1 for (x0, x1) in sections]))
