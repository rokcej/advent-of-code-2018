import math

with open("input") as f:
	bounds = tuple(tuple(int(x) for x in r.split("=")[1].split("..")) for r in f.read().strip().split(", "))

xMin, xMax = min(bounds[0]), max(bounds[0])
yMin, yMax = min(bounds[1]), max(bounds[1])

def Sn(n, a1, d):
	return int(n * (2*a1 + (n-1)*d) // 2)

x1s = []
x1Min = math.ceil((-1 + math.sqrt(1 + 8 * xMin)) / 2)
for x1 in range(x1Min, xMax + 1):
	for n in range(1, x1 + 1):
		if xMin <= Sn(n, x1, -1) <= xMax:
			x1s.append((x1, n))

v1s = set([])
for x1, n in x1s:
	for y1 in range(yMin, -yMin):
		Sy = Sn(n, y1, -1)
		dy = y1 - n
		while Sy >= yMin:
			if Sy <= yMax:
				v1s.add((x1, y1))
				break
			if n < x1:
				break
			Sy += dy
			dy -= 1

print(len(v1s))
