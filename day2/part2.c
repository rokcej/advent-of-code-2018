#include <stdio.h>
#include <string.h>

#define STR_LEN 26
#define N_STR 250

int main() {
	char boxes[N_STR][STR_LEN + 1];
	int box1, box2;

	int i = 0;
	while (scanf("%s", boxes[i]) != EOF) {
		for (int j = 0; j < i; j++) {
			int diff = 0;
			for (int idx = 0; idx < STR_LEN; idx++) {
				if (boxes[i][idx] != boxes[j][idx]) {
					diff++;
					if (diff > 1)
						break;
				}
			}
			if (diff == 1) {
				box1 = i;
				box2 = j;
				break;
			}
		}
		i++;
	}

	char common[STR_LEN];
	int common_idx = 0;
	for (int box_idx = 0; box_idx < STR_LEN; box_idx++) {
		if (boxes[box1][box_idx] == boxes[box2][box_idx])
			common[common_idx++] = boxes[box1][box_idx];
	}
	common[common_idx++] = '\0';

	printf("Result: %s\n", common);

	return 0;
}