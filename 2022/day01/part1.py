with open("input") as f:
	lines = f.read().splitlines()

current_sum = 0
max_sum = 0
for line in lines:
	if len(line) == 0:
		max_sum = max(max_sum, current_sum)
		current_sum = 0
		continue
	current_sum += int(line)
max_sum = max(max_sum, current_sum)

print(max_sum)
