"""
We only need to check positions that are 1 unit of distance outside of each sensor's range.
Find the position that is not in the range of any other sensor.
TODO: Instead of checking each position, treat each of the 4 sides as a line and look for intersections with other sensor ranges.
"""

def get_distance(a, b):
	return abs(a[0] - b[0]) + abs(a[1] - b[1])

def is_detected(pos, sensors):
	for sensor, dist in sensors:
		if get_distance(pos, sensor) <= dist:
			return True
	return False

with open("input", "r") as f:
	lines = f.read().splitlines()

sensors = []
for line in lines:
	tokens = line.split()
	sensor = int(tokens[2][2:-1]), int(tokens[3][2:-1])
	beacon = int(tokens[-2][2:-1]), int(tokens[-1][2:])

	dist = get_distance(sensor, beacon)
	sensors.append((sensor, dist))

distress_beacon = None
for (x0, y0), dist in sensors:
	directions = [
		((x0, y0+dist+1), (+1, -1)), # North -> East
		((x0+dist+1, y0), (-1, -1)), # East  -> South
	    ((x0, y0-dist-1), (-1, +1)), # South -> West
	    ((x0-dist-1, y0), (+1, +1))  # West  -> North
	]
	for (x, y), (dx, dy) in directions:
		for _ in range(dist):
			if 0 <= x <= 4000000 and 0 <= y <= 4000000:
				if not is_detected((x, y), sensors):
					distress_beacon = (x, y)
					break
			x, y = x + dx, y + dy
		if distress_beacon is not None:
			break
	if distress_beacon is not None:
		break

print(distress_beacon[0] * 4000000 + distress_beacon[1])
