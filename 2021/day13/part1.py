dots = set()
folds = []

with open("input") as f:
	lines = f.read().splitlines()
lines_split = lines.index("")
for line in lines[:lines_split]: # Dots
	x, y = line.split(",")
	dots.add((int(x), int(y)))
for line in lines[lines_split+1:]: # Folds
	dim, loc = line.split()[-1].split("=")
	folds.append((ord(dim)-ord("x"), int(loc)))

dim, loc = folds[0]
dots_folded = set()
while dots:
	pos = list(dots.pop())
	if pos[dim] > loc:
		pos[dim] = 2 * loc - pos[dim]
	dots_folded.add(tuple(pos))

print(len(dots_folded))
