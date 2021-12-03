with open("input") as f:
	lines = f.read().splitlines()

ones = [0] * len(lines[0])
for line in lines:
	for i in range(len(line)):
		ones[i] += int(line[i])

gamma = 0
epsilon = 0
for i in range(len(ones)):
	mcb = int(ones[i] >= (len(lines) / 2))
	shift = (len(ones) - 1 - i)
	gamma += mcb << shift
	epsilon +=  (1 - mcb) << shift

print(epsilon * gamma)
