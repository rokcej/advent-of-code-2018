import math

with open("input") as f:
	bounds = tuple(tuple(int(x) for x in r.split("=")[1].split("..")) for r in f.read().strip().split(", "))

xMin, xMax = min(bounds[0]), max(bounds[0])
yMin, yMax = min(bounds[1]), max(bounds[1])

# Arithmetic sum:
# S = n * (n+1) / 2 = n * (a1 + an) / 2 = n * (2*a1 + (n-1)*d) / 2

# n = (-1 + math.sqrt(1 + 8 * xMax)) // 2

# This solution doesn't cover all (theoretical) cases,
# however, it seems to work for this puzzle :)
y1 = -yMin - 1
print(y1 * (y1 + 1) // 2)
