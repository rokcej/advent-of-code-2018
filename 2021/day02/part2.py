print([sum([t[0] for t in z])*sum([t[1] for t in z]) for z in [[(y[0],y[0]*y[1]) for y in [[(x[i][0],sum([a for _,a in x[:i+1]])) for i in range(len(x))] for x in [[({"forward":(v,0),"down":(0,v),"up":(0,-v)}[c]) for c,v in [(l.split()[0],int(l.split()[1])) for l in open("input").read().splitlines()]]]][0]]]][0])

# with open("input", "r") as f:
# 	input = f.read()

# horizontal = 0
# depth = 0
# aim = 0
# for line in input.splitlines():
# 	fields = line.split(" ")
# 	dir = fields[0]
# 	dist = int(fields[1])

# 	if dir == "forward":
# 		horizontal += dist
# 		depth += aim * dist
# 	elif dir == "down":
# 		aim += dist
# 	else:
# 		aim -= dist
	
# print(horizontal * depth)
