from collections import Counter

CARD_ORDER = ["2", "3", "4", "5", "6", "7", "8", "9", "T", "J", "Q", "K", "A"]

with open("input") as f:
	lines = f.read().splitlines()

hands = []
for line in lines:
	hand, bid_str = line.split()
	primary_value = sorted(Counter(hand).values(), reverse=True)
	secondary_value = [CARD_ORDER.index(card) for card in hand]
	hands.append((hand, int(bid_str), (primary_value, secondary_value)))
	
# Exploit the fact that sorting of lists/tuples is done with element-wise comparisons from left to right
hands.sort(key=lambda h: h[2])
print(sum(bid * (i + 1) for i, (_, bid, _) in enumerate(hands)))
