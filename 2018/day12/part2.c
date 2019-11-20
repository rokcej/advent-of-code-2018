#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Match {
	char pattern[6];
	char replace;
} Match;

int main() {
	char *plants = malloc(200100 * sizeof(char));
	char *pending = malloc(200100 * sizeof(char));
	memset(plants, '.', 200100 * sizeof(char));
	memset(pending, 0, 200100 * sizeof(char));
	plants += 100000;
	pending += 100000;	

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

	int max_sums = 64;
	int *sums = malloc(max_sums * sizeof(int));
	int n_sums = 0;

	long long result = 0LL;
	int repeat_count = 0;
	for (int gen = 0; 1; ++gen) {
		if (n_sums >= max_sums) {
			max_sums <<= 1;
			sums = realloc(sums, max_sums * sizeof(int));
		}
		sums[n_sums] = 0;
		for (int i = iBegin; i <= iEnd; ++i) {
			if (plants[i] == '#')
				sums[n_sums] += i;
		}
		++n_sums;

		if (n_sums > 1) {
			int diff = sums[n_sums-1] - sums[n_sums-2];
			if (diff == sums[n_sums-2] - sums[n_sums-3]) {
				repeat_count++;
				if (repeat_count > n_sums/2) {
					result = (50000000000LL - (long long)gen) * (long long)diff + (long long)sums[n_sums-1];
					break;
				}
			} else {
				repeat_count = 0;
			}
		}

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

	printf("%lld\n", result);

	return 0;
}
