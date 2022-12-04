with open("input") as f:
	lines = f.read().splitlines()

count = 0
for line in lines:
	first, second = [[int(val) for val in span.split("-")] for span in line.split(",")]
	if first[0] <= second[0] and first[1] >= second[1] or second[0] <= first[0] and second[1] >= first[1]:
		count += 1

print(count)
