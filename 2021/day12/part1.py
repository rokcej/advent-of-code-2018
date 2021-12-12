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
bfs = [("start", set())]
while len(bfs) > 0:
	node, visited = bfs.pop()
	for edge in nodes[node]:
		if edge == "start" or edge in visited:
			continue
		if edge == "end":
			result += 1
			continue
		visited_new = visited.copy()
		if edge[0].islower():
			visited_new.add(edge)
		bfs.append((edge, visited_new))
print(result)
