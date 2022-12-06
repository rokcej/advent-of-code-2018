with open("input") as f:
	line = f.read()

counts = { chr(i): 0 for i in range(ord("a"), ord("z") + 1) }
duplicates = 0

for c in line[:4]:
	counts[c] += 1
	duplicates += int(counts[c] == 2)

idx = 4
while duplicates > 0:
	c_old, c_new = line[idx-4], line[idx]

	counts[c_old] -= 1
	duplicates -= int(counts[c_old] == 1)
	counts[c_new] += 1
	duplicates += int(counts[c_new] == 2)

	idx += 1

print(idx)
