with open("input") as f:
	start = tuple(int(l.split()[-1]) for l in f.read().splitlines())

rolls = { 3: 1, 4: 3, 5: 6, 6: 7, 7: 6, 8: 3, 9: 1 } # Sum of 3 rolls -> number of possibilities

cache = {} # Memoization
def dfs(score, pos, count): # Index 0 represents the player whose turn it is
	if score[1] >= 21:
		return [0, count]

	state = (score, pos)
	if state in cache:
		cached_wins = cache[state]
		return [cached_wins[0] * count, cached_wins[1] * count]

	wins = [0, 0]
	for roll, universes in rolls.items():
		new_pos_reversed = (pos[1], (pos[0] + roll - 1) % 10 + 1)
		new_score_reversed = (score[1], score[0] + new_pos_reversed[1])

		new_wins_reversed = dfs(new_score_reversed, new_pos_reversed, universes)
		wins[0] += new_wins_reversed[1]
		wins[1] += new_wins_reversed[0]

	cache[state] = wins
	return [wins[0] * count, wins[1] * count]

wins = dfs((0, 0), start, 1)
print(max(wins))
