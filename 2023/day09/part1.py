import numpy as np

def extrapolate_next(history):
	sequences = [history]
	while any(sequences[-1]):
		sequences.append(np.diff(sequences[-1]))
	last_values = [seq[-1] for seq in sequences[:-1]]
	return sum(last_values)

with open("input") as f:
	lines = f.read().splitlines()

histories = [np.fromstring(line, dtype=int, sep=" ") for line in lines]
predictions = map(extrapolate_next, histories)
print(sum(predictions))
