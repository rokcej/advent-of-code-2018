def compute(a, b, op):
	if op == "+": return a + b
	elif op == "-": return a - b
	elif op == "*": return a * b
	else: return a // b

def evaluate(id, values, expressions):
	if id in values:
		return values[id]

	a = evaluate(expressions[id][0], values, expressions)
	b = evaluate(expressions[id][2], values, expressions)
	op = expressions[id][1]
	values[id] = compute(a, b, op)

	return values[id]

with open("input", "r") as f:
	lines = f.read().splitlines()

values, expressions = {}, {}
for line in lines:
	id, expr = line.split(": ")
	if expr[0].isnumeric():
		values[id] = int(expr)
	else:
		expressions[id] = expr.split()

print(evaluate("root", values, expressions))
