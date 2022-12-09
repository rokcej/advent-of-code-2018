import numpy as np

with open("input") as f:
	lines = f.read().splitlines()

rope = [np.array([0, 0]) for _ in range(10)]
visited = {(0, 0)}
dirs = {"L": np.array([0,-1]), "R": np.array([0,+1]), "U": np.array([+1,0]), "D": np.array([-1,0])}

for line in lines:
	delta = dirs[line[0]]
	steps = int(line[2:])

	for _ in range(steps):
		rope[0] += delta
		for i in range(1, len(rope)):
			diff = rope[i-1] - rope[i]	
			if np.max(np.abs(diff)) > 1:
				rope[i] += np.clip(diff, -1, 1)
		visited.add((rope[-1][0], rope[-1][1]))

print(len(visited))
