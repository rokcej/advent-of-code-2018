import numpy as np

nodes = {}
with open("input") as f:
	for line in f.read().splitlines():
		a, b = line.split("-")
		if a in nodes: nodes[a].append(b)
		else: nodes[a] = [b]
		if b in nodes: nodes[b].append(a)
		else: nodes[b] = [a]

result = 0
bfs = [("start", set(), False)]
while len(bfs) > 0:
	node, visited, twice = bfs.pop()
	for edge in nodes[node]:
		if edge == "start" or edge in visited and twice:
			continue
		if edge == "end":
			result += 1
			continue
		twice_new = twice or (edge in visited)
		visited_new = visited.copy()
		if edge[0].islower():
			visited_new.add(edge)
		bfs.append((edge, visited_new, twice_new))
print(result)
