import math

def get_win_count(race_time, record_distance):
	# Solve: x * (race_time - x) > record_distance
	min_solution = (race_time - math.sqrt(race_time * race_time - 4 * record_distance)) / 2
	min_hold_time = math.floor(min_solution + 1)
	max_hold_time = race_time - min_hold_time # Possible because of symmetry
	return max_hold_time - min_hold_time + 1

with open("input") as f:
	lines = f.read().splitlines()

race_times = [int(t) for t in lines[0].split()[1:]]
record_distances = [int(d) for d in lines[1].split()[1:]]
win_counts = [get_win_count(t, d) for t, d in zip(race_times, record_distances)]
print(math.prod(win_counts))
