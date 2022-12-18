def is_within_bounds(pos, min_bound, max_bound):
	return (min_bound[0] <= pos[0] <= max_bound[0] and
	        min_bound[1] <= pos[1] <= max_bound[1] and
	        min_bound[2] <= pos[2] <= max_bound[2])

with open("input", "r") as f:
	lines = f.read().splitlines()

lava = set()
for line in lines:
	lava.add(tuple(int(i) for i in line.split(",")))

min_bound, max_bound = next(iter(lava)), next(iter(lava))
for pos in lava:
	min_bound = tuple(min(mb, p-1) for mb, p in zip(min_bound, pos))
	max_bound = tuple(max(mb, p+1) for mb, p in zip(max_bound, pos))

outside = {min_bound} 
dfs = [min_bound]
while len(dfs) > 0:
	x, y, z = dfs.pop()
	for neighbor in [(x-1,y,z), (x+1,y,z), (x,y-1,z), (x,y+1,z), (x,y,z-1), (x,y,z+1)]:
		if is_within_bounds(neighbor, min_bound, max_bound):
			if neighbor not in outside and neighbor not in lava:
				outside.add(neighbor)
				dfs.append(neighbor)

count = 0
for x, y, z in lava:
	for neighbor in [(x-1,y,z), (x+1,y,z), (x,y-1,z), (x,y+1,z), (x,y,z-1), (x,y,z+1)]:
		if neighbor in outside:
			count += 1
print(count)
