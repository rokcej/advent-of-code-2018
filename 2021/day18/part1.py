with open("input") as f:
	lines = f.read().splitlines()

numbers = []
for line in lines:
	number = []
	for c in line:
		if c in ["[", "]"]:
			number.append(c)
		elif c == ",":
			continue
		else:
			number.append(int(ord(c) - ord("0")))
	numbers.append(number)

def reduce(number):
	recheck = True
	while recheck:
		recheck = False
		exploded = True
		while exploded:
			exploded = False
			depth = 0
			for i in range(len(number)):
				if number[i] == "[":
					depth += 1
				elif number[i] == "]":
					depth -= 1
				else:
					if depth > 4:
						exploded = True
						for j in range(2, i):
							if isinstance(number[i-j], int):
								number[i-j] += number[i]
								break
						for j in range(i+2, len(number)-1):
							if isinstance(number[j], int):
								number[j] += number[i+1]
								break
						number = number[:i-1] + [0] + number[i+3:]
						break
		for i in range(len(number)):
			if isinstance(number[i], int) and number[i] > 9:
				recheck = True
				div = number[i] >> 1
				mod = number[i] & 1
				number = number[:i] + ["[", div, div+mod, "]"] + number[i+1:]
				break
	return number    

def magnitude(number, i):
	vals = [0, 0]
	for v in range(2):
		if number[i] == "[":
			vals[v], i = magnitude(number, i+1)
		else:
			vals[v] = number[i]
			i += 1
	
	return 3 * vals[0] + 2 * vals[1], i+1

current = numbers[0]
for i in range(1, len(numbers)):
	current = ["["] + current + numbers[i] + ["]"]
	current = reduce(current)

result, _ = magnitude(current, 1)
print(result)
