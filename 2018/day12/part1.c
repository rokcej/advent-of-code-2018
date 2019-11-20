#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Match {
	char pattern[6];
	char replace;
} Match;

int main() {
	char *plants = malloc(200 * sizeof(char));
	char *pending = malloc(200 * sizeof(char));
	memset(plants, '.', 200 * sizeof(char));
	memset(pending, 0, 200 * sizeof(char));
	plants += 50;
	pending += 50;	

	char init[101];
	scanf("initial state: %100s\n\n", init);
	for (int i = 0; i < 100; ++i)
		plants[i] = init[i];

	Match matches[32];
	for (int i = 0; i < 32; ++i)
		scanf("%5s => %c\n", matches[i].pattern, &matches[i].replace);

	int iBegin = -4;
	int iEnd = 103;

	int iMin = iBegin;
	int iMax = iEnd;

	for (int gen = 1; gen <= 20; ++gen) {
		for (int i = iBegin; i <= iEnd; ++i) {
			for (int j = 0; j < 32; ++j) {
				if (strncmp(&plants[i], matches[j].pattern, 5) == 0) {
					pending[i+2] = matches[j].replace;
					if (matches[j].replace == '#') {
						if (i-2 < iMin)
							iMin = i-2;
						if (i+2 > iMax)
							iMax = i+2;
					}
					break;
				}
			}
		}
		for (int i = iBegin + 2; i <= iEnd + 2; ++i) {
			if (pending[i]) {
				plants[i] = pending[i];
				pending[i] = 0;
			}
		}
		
		iBegin = iMin;
		iEnd = iMax;
	}

	int result = 0;
	for (int i = iBegin-2; i <= iEnd+2; ++i) {
		if (plants[i] == '#')
			result += i;
	}
	printf("%d\n", result);

	return 0;
}
