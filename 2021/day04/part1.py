with open("input") as f:
	lines = f.read().splitlines()

draws = [int(number) for number in lines[0].split(",")]
maps = [{int(s):(y,x) for y in range(5) for x,s in enumerate(lines[i+y].split())} for i in range(2,len(lines),6)]
boards = [[[0 for _ in range(5)] for _ in range(5)] for _ in range(len(maps))]

for draw in draws:
	winner = -1
	for i in range(len(boards)):
		if draw in maps[i]:
			y, x = maps[i][draw]
			boards[i][y][x] = 1
			if sum(boards[i][y]) == 5 or sum([boards[i][j][x] for j in range(5)]) == 5:
				winner = i
				break
	if winner != -1:
		unmarked_sum = sum([(1-boards[winner][y][x])*num for num,(y,x) in maps[winner].items()])
		print(draw * unmarked_sum)
		break
