with open("input") as f:
	initial = [int(x) for x in f.read().split(",")]

sim = [0]
f = [1]
for day in range(128):
	n = len(sim)
	for i in range(n):
		sim[i] -= 1
		if sim[i] < 0:
			sim[i] = 6
			sim.append(8)
	f.append(len(sim))

for day in range(128):
	val = 0
	for x in sim:
		val += f[max(0, day+1-x)]
	f.append(val)

result = 0
for x in initial:
	result += f[-(x+1)]

print(result)
