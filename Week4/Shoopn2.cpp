#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define MAX 10005
int str[MAX];
int inc[MAX];
int dec[MAX];
int length;

int longestShoop();

int main() {
	while(scanf("%d\n", &length) != EOF) {
		for (int i=0; i<length; i++) {
			scanf("%d", &str[i]);
		}
		int maxS = longestShoop();

		printf("%d\n", maxS+maxS-1);

		for (int i=0; i<length; i++) {
			printf("%d ", inc[i]);
		}
		putchar('\n');
        for (int i=0; i<length; i++) {
            printf("%d ", dec[i]);
        }
        putchar('\n');


	}
	return 0;
}

int longestShoop() {
	int maxI = 1;
	int maxD = 1;
	for (int i = 0; i < length; i++) {
		inc[i] = 1;
		dec[i] = 1;
		for (int j = 0; j < i; j++) {
			// Increasing
			if (str[j] < str[i]) {
				if (inc[j] + 1 > inc[i]) {
					inc[i] = inc[j] + 1;
				}
			}
			if (inc[i] > maxI) {
				maxI = inc[i];
			}
			// Decreasing
            if (str[j] > str[i]) {
                if (dec[j] + 1 > dec[i]) {
                    dec[i] = dec[j] + 1;
                }
            }
			if (dec[i] > maxD) {
				maxD = dec[i];
			}
		}
	}
	return std::min(maxI, maxD);
}

