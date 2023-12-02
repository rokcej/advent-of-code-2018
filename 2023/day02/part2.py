import functools

def get_game_power(record):
	maxima = {"red": 0, "green": 0, "blue": 0}
	_, body = record.split(": ")
	for reveal in body.split("; "):
		for cube in reveal.split(", "):
			count_str, color = cube.split(" ")
			maxima[color] = max(int(count_str), maxima[color])
	return functools.reduce(lambda x, y: x * y, maxima.values())

with open("input") as f:
	lines = f.read().splitlines()

game_power_sum = 0
for line in lines:
	game_power_sum += get_game_power(line)
print(game_power_sum)
