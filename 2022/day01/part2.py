with open("input") as f:
	lines = f.read().splitlines()

current_sum = 0
sums = []
for line in lines:
	if len(line) == 0:
		sums.append(current_sum)
		current_sum = 0
		continue
	current_sum += int(line)
sums.append(current_sum)

print(sum(sorted(sums, reverse=True)[:3]))
