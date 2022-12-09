import numpy as np

with open("input") as f:
	lines = f.read().splitlines()

head = np.array([0, 0])
tail = np.array([0, 0])
visited = {(0, 0)}
dirs = { "L": np.array([0,-1]), "R": np.array([0,+1]), "U": np.array([+1,0]), "D": np.array([-1,0]) }

for line in lines:
	delta = dirs[line[0]]
	steps = int(line[2:])

	for _ in range(steps):
		head += delta
		diff = head - tail
		if np.max(np.abs(diff)) > 1:
			tail += np.clip(diff, -1, 1)
			visited.add((tail[0], tail[1]))

print(len(visited))
