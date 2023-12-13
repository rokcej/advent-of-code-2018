import functools

def get_valid_starts(springs, size):
	starts = []
	for i in range(len(springs) - size + 1):
		j = i + size - 1
		if all(s in ["#", "?"] for s in springs[i:j+1]):
			is_left_valid = i == 0 or springs[i-1] != "#"
			is_right_valid = j == len(springs) - 1 or springs[j+1] != "#"
			if is_left_valid and is_right_valid:
				starts.append(i)
	return starts

@functools.cache
def get_arrangement_count(springs, order):
	if not order:
		return int("#" not in springs)
	if sum(order) + len(order) - 1 > len(springs):
		return 0

	arrangement_count = 0
	size = order[0]
	lookup_count = springs.index("#") + size + 1 if "#" in springs else len(springs)
	starts = get_valid_starts(springs[:lookup_count], size)
	for start in starts:
		arrangement_count += get_arrangement_count(springs[start+size+1:], order[1:]) # Awooga
	return arrangement_count

with open("input") as f:
	lines = f.read().splitlines()

records = []
for line in lines:
	springs, order_str = line.split()
	order = tuple(map(int, order_str.split(",")))
	records.append((springs, order))

print(sum(get_arrangement_count(springs, order) for springs, order in records))
