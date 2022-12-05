with open("input") as f:
	lines = f.read().splitlines()

stacks = [[] for _ in range((len(lines[0]) + 1) // 4)]
i_empty = lines.index("")
for i in range(i_empty - 2, -1, -1):
	for j in range(len(stacks)):
		crate = lines[i][4*j+1]
		if crate != " ":
			stacks[j].append(crate)

for line in lines[i_empty+1:]:
	values = line.split(" ")
	count, src, dst = int(values[1]), int(values[3]) - 1, int(values[5]) - 1
	stacks[dst] += stacks[src][-count:]
	stacks[src] = stacks[src][:-count]

print(''.join([stack[-1] for stack in stacks]))
