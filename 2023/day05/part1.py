def get_maps(lines):
	maps = []
	for line in lines[2:]:
		if not line:
			continue
		if line.endswith("map:"):
			maps.append([])
			continue
		destination, source, count = (int(value) for value in line.split())
		maps[-1].append((destination, source, count))
	return maps

def apply_map(value, map):
	for destination, source, count in map:
		if source <= value < source + count:
			return destination + value - source
	return value

def apply_maps(value, maps):
	mapped_value = value
	for map in maps:
		mapped_value = apply_map(mapped_value, map)
	return mapped_value

with open("input") as f:
	lines = f.read().splitlines()

seeds = [int(seed) for seed in lines[0][7:].split()]
maps = get_maps(lines)
print(min(apply_maps(seed, maps) for seed in seeds))
