#include <cstdlib>
#include <stdio.h>



int main() {
	int cases;
	scanf("%d", &cases);
	for (int c=0; c<cases; c++) {
		bool first = false;
		bool last = false;
		int N, Y, X;
		scanf("%d %d %d", &N, &X, &Y); // #problems, easy, hard
		for (int i=0; i<N; i++) {
			int curr;
			scanf("%d", &curr);
			if (i == 0 && curr == X) { // Easiest, shouldnt be
				first = true;
			} else if (i == N-1 && curr == Y) { // Hardest, shouldnt be
				last = true;
			}
		}
		if (first == true && last == true) {
			printf("BOTH\n");
		} else if (first == true) {
			printf("EASY\n");
		} else if (last == true) {
			printf("HARD\n");
		} else {
			printf("OKAY\n");
		}

	}
	return 0;
}
