with open("input") as f:
	lines = f.read().splitlines()

priority_sum = 0
for i in range(0, len(lines), 3):
	sets = [set(lines[i+j]) for j in range(3)]
	common = list(set.intersection(*sets))[0]
	
	if ord(common) >= ord("a"):
		priority_sum += ord(common) - ord("a") + 1
	else:
		priority_sum += ord(common) - ord("A") + 27

print(priority_sum)
