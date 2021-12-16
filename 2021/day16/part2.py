with open("input") as f:
	hex = f.read().strip()

bin = []
for x in hex:
	val = (ord(x) - ord('0')) if (ord(x) <= ord('9')) else (ord(x) - ord('A') + 10)
	for i in range(4):
		bin.append((val >> (3-i)) & 1)

def bin2dec(bin_list):
	val = 0
	for i in range(len(bin_list)):
		val = (val << 1) | bin_list[i]
	return val

def parse(bin, i):
	ver = bin2dec(bin[i:i+3])
	typ = bin2dec(bin[i+3:i+6])
	i += 6

	if typ == 4:
		literal = 0
		while True:
			group = bin[i:i+5]
			i += 5
			literal = (literal << 4) | bin2dec(group[1:])
			if group[0] == 0:
				break
		return i, literal
	else:
		values = []
		length_type_id = bin[i]
		i += 1
		if length_type_id == 0:
			total_len = bin2dec(bin[i:i+15])
			i += 15

			end_index = i + total_len
			while i < end_index:
				i, subpacket_value = parse(bin, i)
				values.append(subpacket_value)
		else:
			num_subpackets = bin2dec(bin[i:i+11])
			i += 11

			for _ in range(num_subpackets):
				i, subpacket_value = parse(bin, i)
				values.append(subpacket_value)
		
		value = 0
		if typ == 0: # Sum
			value = sum(values)
		elif typ == 1: # Product
			value = values[0]
			for p in range(1, len(values)): value *= values[p]
		elif typ == 2: # Minimum
			value = min(values)
		elif typ == 3: # Maximum
			value = max(values)
		elif typ == 5: # Greater than
			value = int(values[0] > values[1])
		elif typ == 6: # Less than
			value = int(values[0] < values[1])
		elif typ == 7: # Equal to
			value = int(values[0] == values[1])

		return i, value

_, result = parse(bin, 0)
print(result)
