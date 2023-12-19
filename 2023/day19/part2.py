# Split span into true and false parts by comparing it with the value parameter
def split_span(span, compare_greater, value):
	start, stop = span

	span_true, span_false = None, None
	if compare_greater:
		if start > value:
			span_true = span
		elif stop <= value:
			span_false = span
		else:
			span_true = (value + 1, stop)
			span_false = (start, value)
	else:
		if stop < value:
			span_true = span
		elif start >= value:
			span_false = span
		else:
			span_true = (start, value - 1)
			span_false = (value, stop)

	return span_true, span_false

with open("input") as f:
	lines = f.read().splitlines()

i_empty = lines.index("")

# Parse workflows
workflows = dict()
for line in lines[:i_empty]:
	i_bracket = line.find("{")
	name = line[:i_bracket]
	*fields, unconditional_outcome = line[i_bracket+1:-1].split(",")
	rules = []
	for field in fields:
		i_colon = field.find(":")
		category = field[0]
		compare_greater = field[1] == ">"
		value = int(field[2:i_colon])
		outcome = field[i_colon+1:]
		rules.append((category, compare_greater, value, outcome))
	workflows[name] = (rules, unconditional_outcome)

# Represent all possible values using ranges
initial_part = {category: (1, 4000) for category in "xmas"}
initial_status = "in"

# Compute all possible combinations
result = 0
search = [(initial_part, initial_status)]
while len(search) > 0:
	part, status = search.pop() # DFS

	# If outcome is known, compute number of combinations
	if status in ["A", "R"]:
		if status == "A":
			combination_count = 1
			for start, stop in part.values():
				combination_count *= stop - start + 1
			result += combination_count
		continue

	# Apply rules and split parts into two states when necessary
	rules, unconditional_outcome = workflows[status]
	for category, compare_greater, value, outcome in rules:
		span = part[category]
		span_true, span_false = split_span(span, compare_greater, value)
		if span_true is not None:
			part2 = dict(part) # Copy
			part2[category] = span_true
			search.append((part2, outcome))
		if span_false is None:
			break
		part[category] = span_false
	search.append((part, unconditional_outcome))

print(result)
