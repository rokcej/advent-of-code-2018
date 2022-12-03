with open("input") as f:
	lines = f.read().splitlines()

priority_sum = 0
for line in lines:
	first = set(line[:len(line)//2])
	second = set(line[len(line)//2:])
	common = list(first.intersection(second))[0]

	if ord(common) >= ord("a"):
		priority_sum += ord(common) - ord("a") + 1
	else:
		priority_sum += ord(common) - ord("A") + ord("z") - ord("a") + 2

print(priority_sum)
