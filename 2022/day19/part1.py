import re
import numpy as np

def dfs(resources, robots, max_robots, minutes, blueprint, cache, best_result):
	# Check if current state has already been processed
	key = (tuple(resources), tuple(robots), minutes)
	if key in cache:
		return cache[key]

	# Compute number of geodes if we stop producing robots
	geodes = resources[3] + minutes * robots[3]
	if minutes <= 1:
		return geodes

	# Assume we produce 1 geode robot every remaining minute to get the upper bound for the number of geodes
	# If the upper bound is lower than the best result so far, prune the branch
	upper_bound = geodes + (minutes * (minutes - 1)) // 2
	if upper_bound <= best_result[0]:
		return -1
	
	# Select each type of robot and try to build it
	is_zero, not_zero = robots == 0, robots != 0
	for i, required in enumerate(blueprint):
		# Check if we already have enough robots of this type (except for geode robots)
		if i != 3 and robots[i] >= max_robots[i]:
			continue

		# Check if we can produce the required resources to build this robot
		missing = np.maximum(required - resources, 0)
		if np.any(missing[is_zero]):
			continue
		
		# Check if this robot can be built before we run out of time
		wait = np.amax(-(missing[not_zero] // -robots[not_zero])) + 1 # Trick to achieve ceiling division
		if wait > minutes:
			continue

		new_resources = resources + wait * robots - required
		robots[i] += 1
		geodes = max(geodes, dfs(new_resources, robots, max_robots, minutes - wait, blueprint, cache, best_result))
		robots[i] -= 1
	
	cache[key] = geodes
	best_result[0] = max(best_result[0], geodes)
	return geodes


with open("input", "r") as f:
	lines = f.read().splitlines()

blueprints = []
for line in lines:
	id, a, b, c, d, e, f = map(int, re.findall(r"\d+", line)) # Stolen from u/4HbQ
	blueprints.append((id, np.array([
		[a, 0, 0, 0], # Ore robot
		[b, 0, 0, 0], # Clay robot
		[c, d, 0, 0], # Obsidian robot
		[e, 0, f, 0]  # Geode robot
	])))

quality_sum = 0
for id, blueprint in blueprints:
	initial_resources = np.array([0, 0, 0, 0])
	initial_robots = np.array([1, 0, 0, 0])
	# Max number of robots we need to build for this blueprint (except for geode robots)
	max_robots = np.amax(blueprint, axis=0) 

	quality_sum += id * dfs(initial_resources, initial_robots, max_robots, 24, blueprint, {}, [0])
print(quality_sum)
