import numpy as np
import math

with open("input") as f:
	crabs = np.array([int(x) for x in f.read().split(",")], dtype=np.int)
average = np.average(crabs)
S = lambda n: n * (n+1) // 2
results = []
for target in range(math.floor(average), math.ceil(average) + 1):
	results.append(sum([S(abs(crab - target)) for crab in crabs]))
print(min(results))
