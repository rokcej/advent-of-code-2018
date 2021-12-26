# Inspired by Janez Demšar's solution

import queue

def can_move_hr(hall, i, r): # Hall index to room index
	if i < r + 1:
		for j in range(i+1, r+2):
			if hall[j] != -1:
				return False
	elif i > r + 2:
		for j in range(r+2, i):
			if hall[j] != -1:
				return False
	return True

def can_move_rr(hall, r1, r2): # Room index to room index
	for i in range(min(r1,r2)+2, max(r1,r2)+2):
		if hall[i] != -1:
			return False
	return True

def get_distance_hr(i, r):
	return abs([0, 1, 3, 5, 7, 9, 10][i] - [2, 4, 6, 8][r])

def get_distance_rr(r1, r2):
	return 2 * abs(r1 - r2)

def get_next_states(energy, hall, rooms, n):
	# Hall -> Room
	for i, r in enumerate(hall):
		if r != -1 and set(rooms[r]) <= {r} and can_move_hr(hall, i, r):
			return [(
				energy + (10 ** r) * (get_distance_hr(i, r) + n - len(rooms[r])),
				hall[:i] + [-1] + hall[i+1:],
				rooms[:r] + [rooms[r] + [r]] + rooms[r+1:]
			)]
	# Room -> Room
	for r1 in range(len(rooms)):
		if len(rooms[r1]) > 0:
			r2 = rooms[r1][-1]
			if r1 != r2 and set(rooms[r2]) <= {r2} and can_move_rr(hall, r1, r2):
				new_rooms = [room[:] for room in rooms]
				new_rooms[r2].append(new_rooms[r1].pop())
				return [(
					energy + (10 ** r2) * (get_distance_rr(r1, r2) + 2*n + 1 - len(rooms[r1]) - len(rooms[r2])),
					hall[:],
					new_rooms
				)]
	# Room -> Hall
	new_states = []
	for r1 in range(len(rooms)):
		if set(rooms[r1]) <= {r1}:
			continue
		r2 = rooms[r1][-1]
		new_rooms = rooms[:r1] + [rooms[r1][:-1]] + rooms[r1+1:]
		for i in range(len(hall)):
			if hall[i] == -1 and can_move_hr(hall, i, r1):
				new_states.append((
					energy + (10 ** r2) * (get_distance_hr(i, r1) + n + 1 - len(rooms[r1])),
					hall[:i] + [r2] + hall[i+1:],
					new_rooms
				))
	return new_states


with open("input") as f:
	lines = f.read().splitlines()

initial_rooms = [[], [], [], []]
for line in lines[2:4]:
	line = line.strip().replace("#", "")
	for i in range(4):
		initial_rooms[i].insert(0, ord(line[i]) - ord("A"))
# Add extra parts to input
for i in range(4):
	extra = [[3, 3], [1, 2], [0, 1], [2, 0]][i]
	initial_rooms[i] = initial_rooms[i][:1] + extra + initial_rooms[i][1:]
n = len(initial_rooms[0])

pqueue = queue.PriorityQueue()
pqueue.put((0, [-1] * 7, initial_rooms))
seen = set()
while not pqueue.empty():
	energy, hall, rooms = pqueue.get()

	key = (tuple(hall), tuple(tuple(r) for r in rooms))
	if key in seen:
		continue
	seen.add(key)

	if all(len(room) == n and all(r == i for r in room) for i, room in enumerate(rooms)):
		print(energy)
		break

	for state in get_next_states(energy, hall, rooms, n):
		pqueue.put(state)
