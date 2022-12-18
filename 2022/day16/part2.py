from collections import deque

class Valve:
	def __init__(self, flow, tunnels):
		self.flow = flow
		self.tunnels = tunnels
		self.open = False

cache = {} # Memoization
def maximize_pressure(id, valves, distances, minutes, bitmask):
	if (id, minutes, bitmask) in cache:
		return cache[(id, minutes, bitmask)]

	pressure = 0
	for i, id2 in enumerate(valves):
		bit = (1 << i)
		if not (bit & bitmask):
			continue
		cost = distances[id][id2] + 1
		if not valves[id2].open and valves[id2].flow > 0 and cost < minutes:
			valves[id2].open = True
			extra = (minutes - cost) * valves[id2].flow
			pressure = max(pressure, maximize_pressure(id2, valves, distances, minutes - cost, bitmask ^ bit) + extra)
			valves[id2].open = False
	cache[(id, minutes, bitmask)] = pressure
	return pressure

with open("input", "r") as f:
	lines = f.read().splitlines()

# Parse input
valves = dict()
for line in lines:
	first, second = line.split("; ")
	id = first[6:8]
	flow = int(first[23:])
	tunnels = second[23:].split(", ") if second.startswith("tunnels") else [second[22:]]	
	valves[id] = Valve(flow, tunnels)

# Compute distance matrix
distances = {}
for id in valves:
	distances[id] = {id: 0}
	bfs = deque([id])
	while len(bfs) > 0:
		id2 = bfs.popleft()
		for id2_neighbor in valves[id2].tunnels:
			if id2_neighbor not in distances[id]:
				distances[id][id2_neighbor] = distances[id][id2] + 1
				bfs.append(id2_neighbor)

# Ignore valves with no flow
nonzero_valves = { id: v for id, v in valves.items() if v.flow > 0 }

# Use a bitmask to specify which nodes can be visited
pressure = 0
ones = (1 << len(nonzero_valves)) - 1
for bitmask in range(ones):
	me = maximize_pressure("AA", nonzero_valves, distances, 26, bitmask)
	elephant = maximize_pressure("AA", nonzero_valves, distances, 26, ones ^ bitmask)
	pressure = max(pressure, me + elephant)
print(pressure)
