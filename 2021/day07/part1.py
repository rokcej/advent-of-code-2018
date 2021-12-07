with open("input") as f:
	crabs = list(map(int, f.read().split(",")))

align_min = sum(crabs)

for x in range(min(crabs), max(crabs)+1):
	align = 0
	for crab in crabs:
		align += abs(crab - x)
	if align < align_min:
		align_min = align

print(align_min)
