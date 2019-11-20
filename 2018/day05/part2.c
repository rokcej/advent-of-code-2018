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

int shorten(char polymer[], int len) {
	int i = 0;
	int iPrev = -1;

	int new_len = len;

	while (i < len) {
		if (polymer[i] != SKIP) {
			if (iPrev == -1) {
				iPrev = i;
			} else {
				if (match(polymer[i], polymer[iPrev])) {
					polymer[i] = SKIP;
					polymer[iPrev--] = SKIP;
					new_len -= 2;
					while (iPrev >= 0) {
						if (polymer[iPrev] != SKIP)
							break;
						iPrev--;
					}
				} else {
					iPrev = i;
				}
			}
		} else {
			new_len--;
		}
		i++;
	}

	return new_len;
}

void copy(char src[], char dest[], int len) {
	int iSrc = 0;
	int iDest = 0;
	while (iDest < len) {
		if (src[iSrc] != SKIP)
			dest[iDest++] = src[iSrc];
		iSrc++;
	}
}

int main() {
	char raw_polymer[LEN + 1];
	scanf("%s", raw_polymer);
	
	int len = shorten(raw_polymer, LEN);

	char polymer[len + 1];
	polymer[len] = '\0';

	int result = len;
	for (char c = 'a'; c <= 'z'; c++) {
		copy(raw_polymer, polymer, len);
		for (int i = 0; i < len; i++) {
			if (polymer[i] == c || polymer[i] == (c + 'A' - 'a'))
				polymer[i] = SKIP;
		}
		int new_len = shorten(polymer, len);
		if (new_len < result)
			result = new_len;
	}
	printf("Result: %d\n", result);

	return 0;
}