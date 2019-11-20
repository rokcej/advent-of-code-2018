#include <stdio.h>
#include <string.h>

#define STR_LEN 26
#define COUNT_LEN ('z' - 'a' + 1)

int main() {
	char str[STR_LEN + 1];
	int two = 0;
	int three = 0;

	while (scanf("%s", str) != EOF) {
		int count[COUNT_LEN];
		memset(count, 0, COUNT_LEN * sizeof(int));

		for (int i = 0; i < STR_LEN; i++) {
			char c = str[i];
			count[c - 'a']++;
		}


		int counted_two = 0;
		int counted_three = 0;
		for (int i = 0; i < COUNT_LEN; i++) {
			if (!counted_two && count[i] == 2) {
				two++;
				counted_two = 1;
			} else if (!counted_three && count[i] == 3) {
				three++;
				counted_three = 1;
			}
		}
	}

	int checksum = two * three;
	printf("Result: %d\n", checksum);
	return 0;
}