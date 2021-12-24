with open("input") as f:
	lines = f.read().splitlines()

num_groups = 14
group_size = len(lines) // num_groups
groups = []
for i in range(num_groups):
	off = i * group_size
	z0 = int(lines[off +  4].split()[2]) # div z z0
	x0 = int(lines[off +  5].split()[2]) # add x x0
	y0 = int(lines[off + 15].split()[2]) # add y y0
	groups.append((z0, x0, y0))

# z0 ∈ {1, 26}
# if z0 ==  1: x0 >= 10  -->  x = 1
# if z0 == 26: x0 < 0

def add_if_lesser(dic, key, val):
	if key not in dic:
		dic[key] = val
	else:
		if val < dic[key]:
			dic[key] = val

print("This should take about 2.5 minutes and 4 GB of RAM")

states = { 0: [] }
for z0, x0, y0 in groups:
	states_new = {}
	for z, inputs in states.items():
		for inp in range(1, 10):
			cond = int(z % 26 + x0 != inp)
			z_new = (z // z0) * (cond * 25 + 1) + cond * (inp + y0)
			add_if_lesser(states_new, z_new, inputs + [inp])
	states = states_new

states = { k: v for k, v in states.items() if k == 0 }
print("".join([str(x) for x in min(states.values())]))
