# Takes around 1 minute to compute

from collections import deque

class Valve:
	def __init__(self, flow, tunnels):
		self.flow = flow
		self.tunnels = tunnels
		self.open = False

def maximize_pressure(id1, id2, wait1, wait2, valves, distances, minutes):
	if wait1 > wait2:
		return maximize_pressure(id2, id1, wait2, wait1, valves, distances, minutes)

	pressure = 0
	for id in valves:
		duration = distances[id1][id] + 1
		if not valves[id].open and valves[id].flow > 0 and duration < minutes:
			if distances[id1][id] > wait2 + distances[id2][id]:
				continue # Skip nodes that can be reached faster by the other agent
			valves[id].open = True
			released = (minutes - duration) * valves[id].flow
			delta = min(duration, wait2)
			pressure = max(pressure, maximize_pressure(id, id2, duration - delta, wait2 - delta, valves, distances, minutes - delta) + released)
			valves[id].open = False
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

nonzero_valves = { id: v for id, v in valves.items() if v.flow > 0 } # Optimization
print(maximize_pressure("AA", "AA", 0, 0, nonzero_valves, distances, 26))
