with open("input") as f:
	outputs = [l.split(" | ")[1].split() for l in f.read().splitlines()]

counts = {i:0 for i in range(2, 8)}
for output in outputs:
	for display in output:
		counts[len(display)] += 1

print(counts[2] + counts[3] + counts[4] + counts[7])
