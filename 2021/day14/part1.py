from collections import Counter

polymer = ""
rules = {}

with open("input") as f:
	lines = f.read().splitlines()
polymer = lines[0]
for line in lines[2:]:
	a, b = line.split(" -> ")
	rules[a] = b

for step in range(10):
	i = len(polymer) - 2
	while i >= 0:
		pair = polymer[i:i+2]
		if pair in rules:
			polymer = polymer[:i+1] + rules[pair] + polymer[i+1:]
		i = i - 1

counter = Counter(polymer)
max_count = max(counter.values())
min_count = min(counter.values())
print(max_count - min_count)
