class Node:
	def __init__(self, value):
		self.prev = None
		self.next = None
		self.value = value


with open("input", "r") as f:
	lines = f.read().splitlines()

# Create linked list
nodes = [Node(int(line)) for line in lines]
for i in range(1, len(nodes)):
	nodes[i].prev = nodes[i-1]
	nodes[i-1].next = nodes[i]
nodes[0].prev = nodes[-1]
nodes[-1].next = nodes[0]

# Mix the numbers
for node in nodes:
	mod = len(nodes) - 1 # -1 because we remove 1 element when mixing
	steps = node.value % mod
	if steps == 0:
		continue
	
	if steps > mod // 2: # Change direction if it's shorter
		steps -= mod

	node.prev.next = node.next
	node.next.prev = node.prev

	it = node.prev
	for _ in range(0, steps): # Handles positive values
		it = it.next
	for _ in range(0, -steps): # Handles negative values
		it = it.prev

	node.next = it.next
	node.prev = it
	node.next.prev = node
	node.prev.next = node

# Sum grove coordinates
result = 0
it = nodes[0]
while it.value != 0:
	it = it.next
for _ in range(3):
	for _ in range(1000):
		it = it.next
	result += it.value
print(result)
