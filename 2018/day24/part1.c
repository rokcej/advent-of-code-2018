// I slightly changed the input by hand to make the parsing easier
// cause I really cba to spend an hour on parsing
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LEN 10

typedef struct _Group {
	int units;
	int hp;
	char weak[2][32];
	char immune[2][32];
	int damage;
	char attack[32];
	int initiative;

	struct _Group *target;
} Group;

int ep(Group *g) {
	return g->units * g->damage;
}

int alive(Group *g) {
	return (g->units > 0);
}

int dmg(Group *atk, Group *def) {
	if (!alive(def) || strcmp(atk->attack, def->immune[0]) == 0 || strcmp(atk->attack, def->immune[1]) == 0)
		return 0;

	int damage = ep(atk);
	if (strcmp(atk->attack, def->weak[0]) == 0 || strcmp(atk->attack, def->weak[1]) == 0)
		damage *= 2;

	return damage;
}

void read(Group *ga[LEN]) {
	for (int i = 0; i < LEN; ++i) {
		ga[i] = malloc(sizeof(Group));
		scanf(
			"%d units each with %d hit points (weak to %s , %s ; immune to %s , %s ) "
			"with an attack that does %d %s damage at initiative %d\n",
			&ga[i]->units, &ga[i]->hp, ga[i]->weak[0], ga[i]->weak[1],
			ga[i]->immune[0], ga[i]->immune[1], &ga[i]->damage, ga[i]->attack, &ga[i]->initiative
		);
		// printf(
		// 	"%d units each with %d hit points (weak to %s , %s ; immune to %s , %s ) "
		// 	"with an attack that does %d %s damage at initiative %d\n",
		// 	ga[i]->units, ga[i]->hp, ga[i]->weak[0], ga[i]->weak[1],
		// 	ga[i]->immune[0], ga[i]->immune[1], ga[i]->damage, ga[i]->attack, ga[i]->initiative
		// );
		// fflush(stdout);
	}
}

void sort(Group *ga[LEN]) {
	for (int i = 1; i < LEN; ++i) {
		int j = i;
		while (j > 0 && (ep(ga[j]) > ep(ga[j-1]) || (ep(ga[j]) == ep(ga[j-1]) && ga[j]->initiative > ga[j-1]->initiative))) {
			Group *tmp = ga[j];
			ga[j] = ga[j-1];
			ga[j-1] = tmp;
			--j;
		}
	}
}

void target(Group *atk[LEN], Group *def[LEN]) {
	int taken[LEN] = { 0 };
	for (int i = 0; i < LEN; ++i) {
		if (!alive(atk[i]))
			continue;

		atk[i]->target = NULL;
		int jMax = 0;
		while (jMax < LEN && (taken[jMax] || !alive(def[jMax])))
			++jMax;
		if (jMax >= LEN)
			continue;
		int damageMax = dmg(atk[i], def[jMax]);
		for (int j = jMax+1; j < LEN; ++j) {
			if (!alive(def[j]) || taken[j])
				continue;
			int damage = dmg(atk[i], def[j]);
			if (damage > damageMax || (damage == damageMax && ep(def[j]) > ep(def[jMax])) ||
			(damage == damageMax && ep(def[j]) == ep(def[jMax]) && def[j]->initiative > def[jMax]->initiative)) {
				jMax = j;
				damageMax = damage;
			}
		}
		if (damageMax > 0) {
			atk[i]->target = def[jMax];
			taken[jMax] = 1;
		}
	}
}

int attack(Group *g[2*LEN]) {
	int count = 0;
	
	for (int i = 0; i < 2*LEN; ++i) {
		if (!alive(g[i]) || g[i]->target == NULL)
			continue;

		int killed = g[i]->target->units;

		g[i]->target->units -= dmg(g[i], g[i]->target) / g[i]->target->hp;
		if (g[i]->target->units < 0)
			g[i]->target->units = 0;

		killed -= g[i]->target->units;
		
		if (killed > 0)
			++count;
	}

	return count;
}

int main() {
	// Read input
	Group *immune[LEN];
	Group *infection[LEN];

	scanf("Immune System:\n");
	read(immune);
	scanf("\nInfection:\n");
	read(infection);

	Group *groups[2*LEN];
	int init = 2*LEN;
	for (int i = 0; i < 2*LEN; ++i) {
		for (int j = 0; j < LEN; ++j) {
			if (immune[j]->initiative == init) {
				groups[i] = immune[j];
				--init;
				break;
			} else if (infection[j]->initiative == init) {
				groups[i] = infection[j];
				--init;
				break;
			}
		}
	}

	int action;
	do {
		int units_immune = 0, units_infection = 0;
		for (int i = 0; i < LEN; ++i) {
			units_immune += immune[i]->units;
			units_infection += infection[i]->units;
		}

		// Select targets
		sort(immune);
		sort(infection);
		target(immune, infection);
		target(infection, immune);

		// Attack
		action = attack(groups);
	} while (action);

	int units_immune = 0, units_infection = 0;
	for (int i = 0; i < LEN; ++i) {
		units_immune += immune[i]->units;
		units_infection += infection[i]->units;
	}

	printf("Result: %d\n", (units_immune == 0 ? units_infection : units_immune));

	return 0;
}
