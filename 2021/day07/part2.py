import numpy as np

with open("input") as f:
	crabs = np.array([int(x) for x in f.read().split(",")], dtype=np.int)
average = int(np.average(crabs))
S = lambda n: n * (n+1) // 2
result = sum([S(abs(crab - average)) for crab in crabs])
print(result)
