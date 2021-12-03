with open("input") as f:
	lines = f.read().splitlines()

n_bits = len(lines[0])

def get_rating(lines, n_bits, is_co2):
	# Bit criteria
	current = lines
	for i in range(n_bits):
		if len(current) == 1:
			break
		filtered = []
		ones = sum([int(val[i]) for val in current])
		keep = int((ones >= (len(current) / 2)) != is_co2) # xor
		for val in current:
			if int(val[i]) == keep:
				filtered.append(val)
		current = filtered
	
	# Binary to decimal
	rating = 0
	for i in range(n_bits):
		rating |= int(current[0][i]) << (n_bits - 1 - i)
	return rating

o2 = get_rating(lines, n_bits, False)
co2 = get_rating(lines, n_bits, True)

print(o2 * co2)
