"""
This solution assumes there is only one occurence of "humn" in the equality.
Find both expressions (one for each side of the equality).
Move all numbers from the expression that contains "humn" to the other one (make sure to correctly invert operations).
Once only "humn" is left, evaluate the other expression.
"""

class Expression():
	# This was the perfect opportunity for polymorphism,
	# but I guess Python doesn't need it
	pass

class Operation(Expression):
	def __init__(self, first: Expression, second: Expression, op: str):
		self.first = first
		self.second = second
		self.op = op
		self.has_variable = first.has_variable or second.has_variable

	def eval(self) -> int: # Solve a op b
		a, b, op = self.first.eval(), self.second.eval(), self.op
		if op == "+": return a + b
		elif op == "-": return a - b
		elif op == "*": return a * b
		else: return a // b

	def eval_inv_first(self, a: int) -> int: # Solve for x: a = x op b
		b, op = self.second.eval(), self.op
		if op == "+": return a - b
		elif op == "-": return a + b
		elif op == "*": return a // b
		else: return a * b

	def eval_inv_second(self, a: int) -> int: # Solve for x: a = b op x
		b, op = self.first.eval(), self.op
		if op == "+": return a - b
		elif op == "-": return b - a
		elif op == "*": return a // b
		else: return b // a

class Value(Expression):
	def __init__(self, val: int):
		self.val = val
		self.has_variable = isinstance(val, str)

	def eval(self) -> int:
		return self.val


def get_expression(id, expressions, unknowns) -> Expression:
	if id in expressions:
		return expressions[id]

	first = get_expression(unknowns[id][0], expressions, unknowns)
	second = get_expression(unknowns[id][2], expressions, unknowns)
	op = unknowns[id][1]

	expr = Operation(first, second, op)
	if not expr.has_variable:
		expr = Value(expr.eval())
	expressions[id] = expr

	return expressions[id]


with open("input", "r") as f:
	lines = f.read().splitlines()

expressions, unknowns = dict(), dict()
for line in lines:
	id, expr = line.split(": ")
	if id == "humn":
		expressions[id] = Value(id)
	elif expr[0].isnumeric():
		expressions[id] = Value(int(expr))
	else:
		unknowns[id] = expr.split()

expr_known = get_expression(unknowns["root"][0], expressions, unknowns)
expr_unknown = get_expression(unknowns["root"][2], expressions, unknowns)
if expr_known.has_variable:
	expr_known, expr_unknown = expr_unknown, expr_known

val = expr_known.eval()
expr = expr_unknown
while isinstance(expr, Operation):
	if expr.first.has_variable:
		val = expr.eval_inv_first(val)
		expr = expr.first
	else:
		val = expr.eval_inv_second(val)
		expr = expr.second
print(val)
