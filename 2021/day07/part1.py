import numpy as np

with open("input") as f:
	crabs = np.array([int(x) for x in f.read().split(",")], dtype=np.int)
median = np.median(crabs).astype(np.int)
result = sum([abs(crab - median) for crab in crabs])
print(result)
