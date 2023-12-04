with open("input") as f:
	lines = f.read().splitlines()

total_points = 0
for line in lines:
	_, lists = line.split(":")
	winning_numbers, chosen_numbers = (set(int(n) for n in numbers.split()) for numbers in lists.split("|"))
	win_count = len(winning_numbers.intersection(chosen_numbers))
	total_points += 1 << (win_count - 1) if win_count else 0
print(total_points)
