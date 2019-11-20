#include <stdio.h>

#define LEN 50000
#define SKIP -1

int match(char a, char b) {
	if (a >= 'A' && a <= 'Z') {
		return ((b >= 'a' && b <= 'z') && ((a + 'a' - 'A') == b));
	} else if (a >= 'a' && a <= 'z') {
		return ((b >= 'A' && b <= 'Z') && ((a + 'A' - 'a') == b));
	}
	return 0;
}

int main() {
	char polymer[LEN + 1];
	scanf("%s", polymer);
	
	int i = 1;
	int iPrev = 0;
	while (i < LEN) {
		if (polymer[i] != SKIP) {
			if (iPrev == -1) {
				iPrev = i;
			} else {
				if (match(polymer[i], polymer[iPrev])) {
					polymer[i] = SKIP;
					polymer[iPrev--] = SKIP;
					while (iPrev >= 0) {
						if (polymer[iPrev] != SKIP)
							break;
						iPrev--;
					}
				} else {
					iPrev = i;
				}
			}
		}
		i++;
	}

	int result = 0;
	for (int j = 0; j < LEN; j++) {
		if (polymer[j] != SKIP)
			result++;
	}
	printf("Result: %d\n", result);

	return 0;
}