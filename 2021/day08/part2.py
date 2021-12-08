entries = []
with open("input") as f:
	for line in f.read().splitlines():
		entry = tuple(list(map(set, s.split())) for s in line.split(" | "))
		entries.append(entry)


result = 0
for obs, out in entries:
	L = {i: [] for i in range(2, 9)}
	for o in obs:
		L[len(o)].append(o)
	D = { 1: L[2][0], 4: L[4][0], 7: L[3][0], 8: L[7][0] }

	i6 = 0
	for i in range(1, 3):
		if not L[6][i].issuperset(D[1]):
			i6 = i
			break
	D[6] = L[6].pop(i6)
	i0 = int(L[6][0].issuperset(D[4]))
	D[0] = L[6][i0]
	D[9] = L[6][1-i0]

	e = next(iter(D[8].difference(D[9])))

	i3 = 0
	for i in range(1, 3):
		if L[5][i].issuperset(D[1]):
			i3 = i
			break
	D[3] = L[5].pop(i3)
	i5 = int(e in L[5][0])
	D[5] = L[5][i5]
	D[2] = L[5][1-i5]

	value = 0
	for o in out:
		value *= 10
		for d in D:
			if D[d] == o:
				value += d
				break
	result += value
			
print(result)
