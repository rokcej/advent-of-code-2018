with open("input") as f:
	positions = [int(l.split()[-1]) for l in f.read().splitlines()]
scores = [0, 0]
die = 1

i_roll = 0
turn = 0
while True:
	positions[turn] += 3 * (die + 1)
	positions[turn] = (positions[turn] - 1) % 10 + 1
	scores[turn] += positions[turn]
	die += 3

	if scores[turn] >= 1000:
		break

	i_roll += 1
	turn = 1 - turn

result = scores[1-turn] * (i_roll + 1) * 3
print(result)
