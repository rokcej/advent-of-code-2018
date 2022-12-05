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
	count, src, dst = [int(val) for val in line.split(" ")[1::2]]
	for _ in range(count):
		stacks[dst-1].append(stacks[src-1].pop())

print(''.join([stack[-1] for stack in stacks]))
