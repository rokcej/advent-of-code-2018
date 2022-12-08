from collections import defaultdict

with open("input") as f:
	lines = f.read().splitlines()

sizes = defaultdict(int)
paths = ["/"]
for line in lines:
	args = line.split()
	if args[0] == "$":
		if args[1] == "cd":
			if args[2] == "/":
				paths = ["/"]
			elif args[2] == "..":
				paths.pop()	
			else:
				paths.append(f"{paths[-1]}{args[2]}/")
		continue
	
	if args[0] != "dir":
		size = int(args[0])
		for path in paths:
			sizes[path] += size

result = 0
for size in sizes.values():
	if size <= 100000:
		result += size
print(result)
