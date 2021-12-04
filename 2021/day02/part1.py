print([sum([t[0] for t in x])*sum([t[1] for t in x]) for x in [[({"forward":(v,0),"down":(0,v),"up":(0,-v)}[c]) for c,v in [(l.split()[0],int(l.split()[1])) for l in open("input")]]]][0])

# with open("input", "r") as f:
# 	input = f.read()

# horizontal = 0
# depth = 0
# for line in input.splitlines():
# 	fields = line.split(" ")
# 	dir = fields[0]
# 	dist = int(fields[1])

# 	if dir == "forward":
# 		horizontal += dist
# 	elif dir == "down":
# 		depth += dist
# 	else:
# 		depth -= dist
	
# print(horizontal * depth)
