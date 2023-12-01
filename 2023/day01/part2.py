PATTERNS = [("0", "zero"), ("1", "one"), ("2", "two"), ("3", "three"), ("4", "four"), ("5", "five"), ("6", "six"), ("7", "seven"), ("8", "eight"), ("9", "nine")]

def get_first_digit(string):
	for i in range(len(string)):
		for digit, patterns in enumerate(PATTERNS):
			if string.startswith(patterns, i):
				return digit
	return None

def get_last_digit(string):
	for i in reversed(range(len(string))):
		for digit, patterns in enumerate(PATTERNS):
			if string.endswith(patterns, 0, i+1):
				return digit
	return None

with open("input") as f:
	lines = f.read().splitlines()

calibration_sum = 0
for line in lines:
	calibration_sum += 10 * get_first_digit(line) + get_last_digit(line)
print(calibration_sum)
