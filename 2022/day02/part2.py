with open("input") as f:
	lines = f.read().splitlines()

score = 0
for line in lines:
	enemy = ord(line[0]) - ord("A")
	outcome = ord(line[2]) - ord("X")
	me = (enemy + outcome + 2) % 3

	score += me + 1
	if me == enemy:
		score += 3
	elif (me + 2) % 3 == enemy:
		score += 6

print(score)
