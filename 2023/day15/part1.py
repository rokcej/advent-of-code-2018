def get_hash(string):
	value = 0
	for character in string:
		value = (value + ord(character)) * 17 % 256
	return value

with open("input") as f:
	lines = f.read().splitlines()

steps = lines[0].split(",")
print(sum(map(get_hash, steps)))
