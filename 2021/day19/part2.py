from collections import defaultdict

with open("input") as f:
	scanner_lines = [s.splitlines()[1:] for s in f.read().split("\n\n")]
	scanners = [[tuple(map(int, l.split(","))) for l in sl] for sl in scanner_lines]

def get_orientations(): # pi = permutation indices, ps = permutation signs
	for ps0, ps1 in [(+1,+1),(+1,-1),(-1,+1),(-1,-1)]:
		for pi in [(0,1,2),(2,0,1),(1,2,0)]:
			yield pi, (ps0,ps1,ps0*ps1)
		for pi in [(0,2,1),(1,0,2),(2,1,0)]:
			yield pi, (ps0,ps1,-ps0*ps1)

def apply_orientation(pos, pi, ps):
	return (pos[pi[0]]*ps[0], pos[pi[1]]*ps[1], pos[pi[2]]*ps[2])

i0s = [0]
offs = {0: (0,0,0)}
while i0s:
	i0 = i0s.pop() # Current known scanner
	for i in range(len(scanners)): # Loop over unknown scanners
		if i in offs:
			continue

		for pi, ps in get_orientations():
			diff_counts = defaultdict(int)
			for _pos in scanners[i]:
				pos = apply_orientation(_pos, pi, ps)
				for pos0 in scanners[i0]:
					diff = tuple(pos0[j]-pos[j] for j in range(3))
					if abs(diff[0]) <= 2000 and abs(diff[1]) <= 2000 and abs(diff[2]) <= 2000:
						diff_counts[diff] += 1
			max_diff = max(diff_counts, key=diff_counts.get)
			if diff_counts[max_diff] >= 12:
				i0s.append(i)
				offs[i] = tuple(offs[i0][j] + max_diff[j] for j in range(3))
				scanners[i] = [apply_orientation(_pos, pi, ps) for _pos in scanners[i]]
				break

max_dist = 0
for a in offs.values():
	for b in offs.values():
		dist = sum([abs(a[i]-b[i]) for i in range(3)])
		if dist > max_dist:
			max_dist = dist
print(max_dist)
