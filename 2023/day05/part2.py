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

def apply_map(input_ranges, map):
	remaining_ranges = [x for x in input_ranges]
	mapped_ranges = []
	for map_destination, map_source, map_count in map:
		a0 = map_source                 # Map source range first index
		a1 = map_source + map_count - 1 # Map source range last index

		new_ranges = []
		for range_start, range_count in remaining_ranges:
			b0 = range_start                   # Input range first index
			b1 = range_start + range_count - 1 # Input range last index

			if a0 > b1 or a1 < b0:
				new_ranges.append((range_start, range_count))
				continue
			c0 = max(b0, a0) # Range intersection first index
			c1 = min(b1, a1) # Range intersection last index

			mapped_ranges.append((c0 + map_destination - map_source, c1 - c0 + 1))
			if c0 > b0:
				new_ranges.append((b0, c0 - b0))
			if c1 < b1:
				new_ranges.append((c1 + 1, b1 - c1))

		remaining_ranges = new_ranges
	return mapped_ranges + remaining_ranges

def apply_maps(input_ranges, maps):
	mapped_ranges = [(start, count) for start, count in input_ranges]
	for map in maps:
		mapped_ranges = apply_map(mapped_ranges, map)
	return mapped_ranges

with open("input") as f:
	lines = f.read().splitlines()

seeds = [int(seed) for seed in lines[0][7:].split()]
seed_ranges = list(zip(seeds[0::2], seeds[1::2]))
maps = get_maps(lines)
location_ranges = apply_maps(seed_ranges, maps)
print(min(start for start, _ in location_ranges))
