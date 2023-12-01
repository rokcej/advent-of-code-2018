def get_first_digit(characters):
	for character in characters:
		digit = ord(character) - ord("0")
		if 0 <= digit <= 9:
			return digit
	return None

with open("input") as f:
	lines = f.read().splitlines()

calibration_sum = 0
for line in lines:
	calibration_sum += 10 * get_first_digit(line) + get_first_digit(reversed(line))
print(calibration_sum)
