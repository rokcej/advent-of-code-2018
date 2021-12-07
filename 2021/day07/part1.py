print([min([sum([abs(c-x) for c in cs]) for x in range(min(cs),max(cs)+1)]) for cs in [list(map(int, open("input").read().split(",")))]][0])

# with open("input") as f:
# 	crabs = list(map(int, f.read().split(",")))

# align_min = sum(crabs)

# for x in range(min(crabs), max(crabs)+1):
# 	align = 0
# 	for crab in crabs:
# 		align += abs(crab - x)
# 	if align < align_min:
# 		align_min = align

# print(align_min)
