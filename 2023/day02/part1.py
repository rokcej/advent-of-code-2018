CUBES = {"red": 12, "green": 13, "blue": 14}

def evaluate_game(record):
	head, body = record.split(": ")
	game_id = int(head.split(" ")[1])
	for cube_set in body.split("; "):
		for cube in cube_set.split(", "):
			count_str, color = cube.split(" ")
			if int(count_str) > CUBES[color]:
				return game_id, False
	return game_id, True

with open("input") as f:
	lines = f.read().splitlines()

game_id_sum = 0
for line in lines:
	game_id, is_valid = evaluate_game(line)
	game_id_sum += int(is_valid) * game_id
print(game_id_sum)
