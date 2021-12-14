from collections import defaultdict

polymer = ""
rules = {}

with open("input") as f:
	lines = f.read().splitlines()
polymer = lines[0]
for line in lines[2:]:
	a, b = line.split(" -> ")
	rules[a] = b

# Store pair counts
pairs = defaultdict(int)
for i in range(0, len(polymer)-1):
	pairs[polymer[i:i+2]] += 1
# Perform insertion steps
for step in range(40):
	pairs_new = defaultdict(int)
	for pair, count in pairs.items():
		if pair in rules:
			insert = rules[pair]
			pairs_new[pair[0] + insert] += count
			pairs_new[insert + pair[1]] += count
		else:
			pairs_new[pair] += count
	pairs = pairs_new

# Count elements
counts = defaultdict(int)
for pair, count in pairs.items():
	counts[pair[0]] += count
	counts[pair[1]] += count
# Correct element counts by removing overlaps
for el, count in counts.items():
	if el == polymer[0] and el == polymer[-1]:
		counts[el] = (count-2)//2 + 2
	elif el == polymer[0] or el == polymer[-1]:
		counts[el] = (count-1)//2 + 1
	else:
		counts[el] //= 2

max_count = max(counts.values())
min_count = min(counts.values())
print(max_count - min_count)
