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

pairs = []
for i in range(0, len(lines), 3):
	# I am ashamed of this line
	exec(f"pairs.append(({lines[i]},{lines[i+1]}))")

result = 0
for i, pair in enumerate(pairs):
	if compare_order(*pair) == 1:
		result += i + 1
print(result)
