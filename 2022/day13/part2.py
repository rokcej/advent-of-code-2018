from functools import cmp_to_key

def compare_order(first, second):
	for i in range(min(len(first), len(second))):
		if isinstance(first[i], list) and isinstance(second[i], list):
			if (order := compare_order(first[i], second[i])) != 0:
				return order
		elif isinstance(first[i], list):
			if (order := compare_order(first[i], [second[i]])) != 0:
				return order
		elif isinstance(second[i], list):
			if (order := compare_order([first[i]], second[i])) != 0:
				return order
		else:
			if first[i] != second[i]:
				return +1 if first[i] < second[i] else -1

	if len(first) != len(second):
		return +1 if len(first) < len(second) else -1
	return 0

with open("input", "r") as f:
	lines = f.read().splitlines()

dividers = ([[2]], [[6]])
packets = [*dividers]
for i in range(0, len(lines), 3):
	# I am ashamed of this line
	exec(f"packets.extend([{lines[i]},{lines[i+1]}])")

packets.sort(key=cmp_to_key(compare_order), reverse=True)
print((packets.index(dividers[0]) + 1) * (packets.index(dividers[1]) + 1))
