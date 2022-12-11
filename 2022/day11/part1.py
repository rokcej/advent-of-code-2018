class Monkey:
	def __init__(self, lines):
		self.items = [int(x) for x in lines[1][18:].split(", ")]
		self.op = lines[2][23:].split() # Operation
		self.div = int(lines[3][21:])   # Divisor
		self.i1 = int(lines[4][29:])    # True index
		self.i0 = int(lines[5][30:])    # False index

with open("input") as f:
	lines = f.read().splitlines()

monkeys = [] # Ook ook!
for i in range(0, len(lines), 7):
	monkeys.append(Monkey(lines[i:i+6]))

counts = { i: 0 for i in range(len(monkeys)) }
for round in range(20):
	for i, monkey in enumerate(monkeys):
		counts[i] += len(monkey.items)
		for worry in monkey.items:
			operand = worry if (monkey.op[1] == "old") else int(monkey.op[1])
			worry = (worry + operand) if (monkey.op[0] == "+") else (worry * operand)
			worry //= 3
			monkeys[monkey.i1 if (worry % monkey.div == 0) else monkey.i0].items.append(worry)
		monkey.items.clear()

first, second = sorted(counts.values(), reverse=True)[:2]
print(first * second)
