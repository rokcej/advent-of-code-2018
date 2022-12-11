with open("input") as f:
	lines = f.read().splitlines()

monkeys = [] # Ook ook!
for i in range(0, len(lines), 7):
	items = [int(x) for x in lines[i+1][18:].split(", ")]
	op = lines[i+2][23:].split()
	test = int(lines[i+3][21:])
	succ = int(lines[i+4][29:])
	fail = int(lines[i+5][30:])
	monkeys.append([items, op, test, succ, fail])

counts = { i: 0 for i in range(len(monkeys)) }
for round in range(20):
	for i, [items, op, test, succ, fail] in enumerate(monkeys):
		counts[i] += len(items)
		while (len(items) > 0):
			worry = items.pop() # Order doesn't matter
			operand = worry if op[1] == "old" else int(op[1])
			worry = worry + operand if op[0] == "+" else worry * operand
			worry //= 3
			monkeys[succ if worry % test == 0 else fail][0].append(worry)

first, second = sorted(counts.values(), reverse=True)[:2]
print(first * second)
