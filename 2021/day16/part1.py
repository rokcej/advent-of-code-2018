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

	ver_sum = ver
	if typ == 4:
		literal = 0
		while True:
			group = bin[i:i+5]
			i += 5
			literal = (literal << 4) | bin2dec(group[1:])
			if group[0] == 0:
				break
		# GG, can't do anything with the value in this part
	else:
		length_type_id = bin[i]
		i += 1
		if length_type_id == 0:
			total_len = bin2dec(bin[i:i+15])
			i += 15

			end_index = i + total_len
			while i < end_index:
				i, subpacket_sum = parse(bin, i)
				ver_sum += subpacket_sum
		else:
			num_subpackets = bin2dec(bin[i:i+11])
			i += 11

			for _ in range(num_subpackets):
				i, subpacket_sum = parse(bin, i)
				ver_sum += subpacket_sum

	return i, ver_sum

_, result = parse(bin, 0)
print(result)
