char2int = {"=": -2, "-": -1, "0": 0, "1": 1, "2": 2}
int2char = {i: c for c, i in char2int.items()} # Invert char2int

def snafu2decimal(snafu: str) -> int:
	# Convert SNAFU to base-10
	decimal = 0
	shift = 1
	for s in reversed(snafu):
		decimal += char2int[s] * shift
		shift *= 5
	return decimal

def decimal2snafu(decimal: int) -> str:
	# Convert base-10 to base-5
	quinary = []
	remainder = decimal
	while remainder > 0:
		quinary.append(remainder % 5)
		remainder //= 5
	
	# Convert base-5 to SNAFU
	snafu = ""
	carry = 0
	for q in quinary:
		s = q + carry
		carry = (s + 2) // 5
		s = (s + 2) % 5 - 2
		snafu += int2char[s]
	if carry > 0:
		snafu += int2char[carry]

	return snafu[::-1] # Reverse


with open("input", "r") as f:
	lines = f.read().splitlines()

sum_decimal = sum(snafu2decimal(line) for line in lines)
print(decimal2snafu(sum_decimal))
