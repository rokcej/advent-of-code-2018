with open("input", "r") as f:
    lines = f.readlines()

depths = [int(line.strip()) for line in lines]
count = 0
window = sum(depths[:3])
for i in range(3, len(depths)):
    new_window = window + depths[i] - depths[i-3]
    if new_window > window:
        count += 1
    window = new_window

print(count)
    