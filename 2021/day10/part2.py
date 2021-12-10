with open("input") as f:
	lines = f.read().splitlines()

start = set(["(", "[", "{", "<"])
match = {"(": ")", "[": "]", "{": "}", "<": ">"}
points = {")": 1, "]": 2, "}": 3, ">": 4}

scores = []
for line in lines:
	stack = []
	corrupted = False
	for c in line:
		if c in start:
			stack.append(c)
		else:
			if c != match[stack.pop()]:
				corrupted = True
				break
	if not corrupted:
		score = 0
		while len(stack) != 0:
			score = score * 5 + points[match[stack.pop()]]
		scores.append(score)

result = sorted(scores)[len(scores)//2]
print(result)

