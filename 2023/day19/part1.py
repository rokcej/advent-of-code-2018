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

# Parse parts
parts = list()
for line in lines[i_empty+1:]:
	equations = line[1:-1].split(",")
	pairs = [equation.split("=") for equation in equations]
	parts.append({category: int(value_str) for category, value_str in pairs})

# Count accepted parts
result = 0
for part in parts:
	status = "in"
	while status not in ["A", "R"]:
		rules, unconditional_outcome = workflows[status]
		passed = False
		for category, compare_greater, value, outcome in rules:
			passed = part[category] > value if compare_greater else part[category] < value
			if passed:
				status = outcome
				break
		if not passed:
			status = unconditional_outcome
	if status == "A":
		result += sum(part.values())
print(result)
