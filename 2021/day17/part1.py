import math

with open("input") as f:
	bounds = tuple(tuple(int(x) for x in r.split("=")[1].split("..")) for r in f.read().strip().split(", "))

xMin, xMax = min(bounds[0]), max(bounds[0])
yMin, yMax = min(bounds[1]), max(bounds[1])

# Here's the main idea: movement on the y-axis is symmetrical.
# If we start at `y = 0` with a vertical velocity y1, we will always reach `y = 0` again after `2*y1 + 1` steps.
# This means that on the next step, we will reach `y = -y1 - 1`.
# To maximize the height, we assume `yMin = -y1 - 1`, therefore `y1 = -yMin - 1`.
# To calculate the maximum height, we use the arithmetic sum formula `Sn = n * (n+1) / 2`.

# This solution doesn't cover all (theoretical) cases,
# however, it seems to work for this puzzle :)

y1 = -yMin - 1
print(y1 * (y1 + 1) // 2)
