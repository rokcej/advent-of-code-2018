import numpy as np

with open("input") as f:
	crabs = np.array([int(x) for x in f.read().split(",")], dtype=np.int)

avg = np.average(crabs)
greater_avg = np.average(crabs > avg)
target = round(avg - greater_avg)

def S(n): return n * (n+1) // 2
result = sum([S(abs(crab - target)) for crab in crabs])
print(result)
