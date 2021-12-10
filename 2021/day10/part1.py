with open("input") as f:
	lines = f.read().splitlines()

start = set(["(", "[", "{", "<"])
match = {"(": ")", "[": "]", "{": "}", "<": ">"}
points = {")": 3, "]": 57, "}": 1197, ">": 25137}

result = 0
for line in lines:
	stack = []
	for c in line:
		if c in start:
			stack.append(c)
		else:
			if c != match[stack.pop()]:
				result += points[c]
				break
print(result)
