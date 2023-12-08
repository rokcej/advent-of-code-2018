# This solution is based on the following assumptions, which aren't mentioned in the instructions:
# a) Each path's cycle offset is the same as its cycle length
# b) Each path can only encounter one "Z" node per cycle
# c) Each path always encounters a "Z" node at the start of the cycle

import re, math

with open("input") as f:
	lines = f.read().splitlines()

directions = [["L", "R"].index(char) for char in lines[0]]
edge_regex = re.compile(r"\w+")
edges = {node: [left, right] for node, left, right in map(edge_regex.findall, lines[2:])}

starting_nodes = [node for node in edges if node.endswith("A")]
cycle_lengths = [0 for _ in range(len(starting_nodes))]
for i, node in enumerate(starting_nodes):
	while not node.endswith("Z"):
		direction = directions[cycle_lengths[i] % len(directions)]
		node = edges[node][direction]
		cycle_lengths[i] += 1
print(math.lcm(*cycle_lengths))
