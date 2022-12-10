with open("input") as f:
	lines = f.read().splitlines()

screen = [["." for _ in range(40)] for _ in range(6)]

pc = 0 # Program counter
remaining = 0
register = 1

for cycle in range(1, 241):
	# Begin cycle
	if remaining == 0:
		remaining = 1 if lines[pc][:4] == "noop" else 2

	# During cycle
	column = (cycle - 1) % 40
	if register - 1 <= column and register + 1 >= column:
		row = (cycle-1) // 40
		screen[row][column] = "#"

	# End cycle
	remaining -= 1
	if remaining == 0:
		if lines[pc][:4] == "addx":
			register += int(lines[pc][5:])
		pc += 1

for row in screen:
	print("".join(row))
