import numpy as np

with open("input") as f:
	lines = f.read().splitlines()

card_counts = np.ones(len(lines), dtype=int)
for i, line in enumerate(lines):
	_, lists = line.split(":")
	winning_numbers, chosen_numbers = (set(int(n) for n in numbers.split()) for numbers in lists.split("|"))
	win_count = len(winning_numbers.intersection(chosen_numbers))
	card_counts[i + 1 : min(i + win_count + 1, len(card_counts))] += card_counts[i]
print(sum(card_counts))
