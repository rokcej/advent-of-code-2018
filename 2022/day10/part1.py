with open("input") as f:
	lines = f.read().splitlines()

signal_sum = 0

pc = 0 # Program counter
remaining = 0
register = 1

for cycle in range(1, 221):
	# Begin cycle
	if remaining == 0:
		remaining = 1 if lines[pc][:4] == "noop" else 2

	# During cycle
	if (cycle + 20) % 40 == 0:
		signal_sum += cycle * register

	# End cycle
	remaining -= 1
	if remaining == 0:
		if lines[pc][:4] == "addx":
			register += int(lines[pc][5:])
		pc += 1

print(signal_sum)
