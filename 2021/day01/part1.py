with open("input", "r") as f:
    lines = f.readlines()

depths = [int(line.strip()) for line in lines]
count = 0
for i in range(1, len(depths)):
    if depths[i] > depths[i-1]:
        count += 1

print(count)
    