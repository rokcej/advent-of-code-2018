import math

with open("input") as f:
	bounds = tuple(tuple(int(x) for x in r.split("=")[1].split("..")) for r in f.read().strip().split(", "))

xMin, xMax = min(bounds[0]), max(bounds[0])
yMin, yMax = min(bounds[1]), max(bounds[1])

def Sn(n, a1, d): # Find sum of n terms starting with a1, where d = a[i+1]-a[i]
	return int(n * (2*a1 + (n-1)*d) // 2)
def inverseSn(S, a1, d): # Find n that sums arithmetic progression to S
	return (d - 2*a1 + math.sqrt((2*a1-d)**2 + 8*d*S)) / (2*d)

x1s = []
x1Min = math.ceil((-1 + math.sqrt(1 + 8 * xMin)) / 2) # Solution of x1Min*(x1Min+1)/2 >= xMin
for x1 in range(x1Min, xMax + 1):
	nMin = math.ceil(inverseSn(xMin, x1, -1))
	nMax = x1
	if Sn(nMax, x1, -1) >= xMax:
		nMax = math.floor(inverseSn(xMax, x1, -1))
	for n in range(nMin, nMax + 1):
		x1s.append((x1, n))

v1s = set()
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
