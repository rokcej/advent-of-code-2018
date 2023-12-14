CYCLE_COUNT = 1_000_000_000

def tilt_horizontally(platform, dx):
	x_range = range(len(platform[0]))
	for x in (x_range if dx < 0 else reversed(x_range)):
		for y in range(len(platform)):
			if platform[y][x] == "O":
				x_new = x
				while 0 <= x_new + dx < len(platform[0]) and platform[y][x_new + dx] == ".":
					x_new += dx
				platform[y][x], platform[y][x_new] = platform[y][x_new], platform[y][x]

def tilt_vertically(platform, dy):
	y_range = range(len(platform))
	for y in (y_range if dy < 0 else reversed(y_range)):
		for x in range(len(platform[0])):
			if platform[y][x] == "O":
				y_new = y
				while 0 <= y_new + dy < len(platform) and platform[y_new + dy][x] == ".":
					y_new += dy
				platform[y][x], platform[y_new][x] = platform[y_new][x], platform[y][x]

def spin_cycle(platform):
	tilt_vertically(platform, -1)
	tilt_horizontally(platform, -1)
	tilt_vertically(platform, +1)
	tilt_horizontally(platform, +1)

def get_total_load(platform):
	total_load = 0
	for y in range(len(platform)):
		for x in range(len(platform[0])):
			total_load += int(platform[y][x] == "O") * (len(platform) - y)
	return total_load

def encode_platform(platform):
	encoding = []
	for row in platform:
		contiguous_groups = []
		offset = 0
		while offset < len(row):
			size = 0
			while offset + size < len(row) and row[offset + size] == "O":
				size += 1
			if size > 0:
				contiguous_groups.append((offset, size))
			offset += size + 1
		encoding.append(tuple(contiguous_groups))
	return tuple(encoding)

with open("input") as f:
	lines = f.read().splitlines()

platform = [list(line) for line in lines]

platform_cache = dict()
loop_offset = None
loop_length = None

cycle = 1
while True:
	spin_cycle(platform)
	encoded_platform = encode_platform(platform)
	total_load = get_total_load(platform)

	if encoded_platform in platform_cache:
		prev_cycle, _ = platform_cache[encoded_platform]
		loop_offset = prev_cycle
		loop_length = cycle - prev_cycle
		break

	platform_cache[encoded_platform] = (cycle, total_load)
	cycle += 1

total_loads = {cycle: load for cycle, load in platform_cache.values()}
loop_index = (CYCLE_COUNT - loop_offset) % loop_length
print(total_loads[loop_offset + loop_index])
