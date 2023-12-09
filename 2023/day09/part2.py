import numpy as np

def extrapolate_previous(history):
	sequences = [history]
	while any(sequences[-1]):
		sequences.append(np.diff(sequences[-1]))
	first_values = [seq[0] for seq in sequences]
	return sum(first_values[0::2]) - sum(first_values[1::2])
	# return functools.reduce(lambda a,b: b-a, (seq[0] for seq in sequences[-2::-1]))

with open("input") as f:
	lines = f.read().splitlines()

histories = [np.fromstring(line, dtype=int, sep=" ") for line in lines]
predictions = map(extrapolate_previous, histories)
print(sum(predictions))
