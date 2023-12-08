from collections import Counter

CARD_ORDER = ["J", "2", "3", "4", "5", "6", "7", "8", "9", "T", "Q", "K", "A"]

with open("input") as f:
	lines = f.read().splitlines()

hands = []
for line in lines:
	hand, bid_str = line.split()
	# Find ideal hand by transforming jokers
	card_counts = Counter(hand)
	ideal_counts = Counter(filter(lambda card: card != "J", hand))
	best_card = max(ideal_counts, key=ideal_counts.get) if ideal_counts else CARD_ORDER[-1]
	ideal_counts[best_card] += card_counts["J"]
	# Use ideal hand for primary ordering
	primary_value = sorted(ideal_counts.values(), reverse=True)
	secondary_value = [CARD_ORDER.index(card) for card in hand]
	hands.append((hand, int(bid_str), (primary_value, secondary_value)))

# Exploit the fact that sorting of lists/tuples is done with element-wise comparisons from left to right
hands.sort(key=lambda h: h[2])
print(sum(bid * (i + 1) for i, (_, bid, _) in enumerate(hands)))
