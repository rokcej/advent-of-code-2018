with open("input") as f:
	lines = f.read().splitlines()

draws = [int(number) for number in lines[0].split(",")]
maps = [{int(s):(y,x) for y in range(5) for x,s in enumerate(lines[i+y].split())} for i in range(2,len(lines),6)]
boards = [[[0 for _ in range(5)] for _ in range(5)] for _ in range(len(maps))]

for draw in draws:
	last_board, last_map = None, None
	i = 0
	while i < len(boards):
		if draw in maps[i]:
			y, x = maps[i][draw]
			boards[i][y][x] = 1
			if sum(boards[i][y]) == 5 or sum([boards[i][j][x] for j in range(5)]) == 5:
				last_board, last_map = boards.pop(i), maps.pop(i)
				continue
		i += 1
	if len(boards) == 0:
		unmarked_sum = sum([(1-last_board[y][x])*num for num,(y,x) in last_map.items()])
		print(draw * unmarked_sum)
		break
