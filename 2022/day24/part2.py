class Blizzard:
	def __init__(self, pos, dir):
		self.pos = pos
		self.dir = dir

def move_blizzards(blizzards, valley):
	for blizz in blizzards:
		(y, x), (dy, dx) = blizz.pos, blizz.dir
		y2 = (y + dy - 1) % (h - 2) + 1
		x2 = (x + dx - 1) % (w - 2) + 1

		valley[y][x] -= 1
		valley[y2][x2] += 1
		blizz.pos = (y2, x2)

def reach_goal(pos_start, pos_goal, blizzards, valley):
	h, w = len(valley), len(valley[0])
	ping, pong = set([pos_start]), set()
	minutes = 1
	while True:
		move_blizzards(blizzards, valley)
		for (y, x) in ping:
			for y2, x2 in [(y, x), (y+1, x), (y-1, x), (y, x-1), (y, x+1)]:
				if not (0 <= y2 < h and 0 <= x2 < w):
					continue
				if valley[y2][x2] != 0:
					continue
				if (y2, x2) == pos_goal:
					return minutes
				pong.add((y2, x2))

		ping, pong = pong, ping
		pong.clear()
		minutes += 1


with open("input", "r") as f:
	lines = f.read().splitlines()

h, w = len(lines), len(lines[0])
valley = [[0 for _ in range(w)] for _ in range(h)]
blizzards = []

dirs = {"^": (+1, 0), "v": (-1, 0), "<": (0, -1), ">": (0, +1)}
for y, line in enumerate(reversed(lines)):
	for x, char in enumerate(line):
		if char in dirs:
			blizzards.append(Blizzard((y, x), dirs[char]))
			valley[y][x] = 1
		elif char == "#":
			valley[y][x] = -1

pos_start = (h-1, valley[h-1].index(0))
pos_goal = (0, valley[0].index(0))

print(
	reach_goal(pos_start, pos_goal, blizzards, valley) + 
	reach_goal(pos_goal, pos_start, blizzards, valley) + 
	reach_goal(pos_start, pos_goal, blizzards, valley)
)
