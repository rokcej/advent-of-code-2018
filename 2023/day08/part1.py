import re

with open("input") as f:
	lines = f.read().splitlines()

directions = [["L", "R"].index(char) for char in lines[0]]
edge_regex = re.compile(r"\w+")
edges = {node: [left, right] for node, left, right in map(edge_regex.findall, lines[2:])}

node = "AAA"
step_count = 0
while node != "ZZZ":
	direction = directions[step_count % len(directions)]
	node = edges[node][direction]
	step_count += 1
print(step_count)
