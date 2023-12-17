def get_hash(string):
	value = 0
	for character in string:
		value = (value + ord(character)) * 17 % 256
	return value

with open("input") as f:
	lines = f.read().splitlines()

steps = lines[0].split(",")
boxes = [[] for _ in range(256)]
for step in steps:
	if step.endswith("-"):
		step_label = step[:-1]
		i_box = get_hash(step_label)
		for i_lens, (label, focal_length) in enumerate(boxes[i_box]):
			if label == step_label:
				boxes[i_box].pop(i_lens)
				break
	else:
		step_label = step[:-2]
		step_focal_length = int(step[-1])
		i_box = get_hash(step_label)
		for i_lens, (label, focal_length) in enumerate(boxes[i_box]):
			if label == step_label:
				boxes[i_box][i_lens] = (step_label, step_focal_length)
				break
		else:
			boxes[i_box].append((step_label, step_focal_length))

focusing_power = 0
for i_box, box in enumerate(boxes):
	for i_lens, (label, focal_length) in enumerate(box):
		focusing_power += (i_box + 1) * (i_lens + 1) * focal_length
print(focusing_power)
