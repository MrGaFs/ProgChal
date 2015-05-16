#include <iostream>
#include <stdio.h>
#include <stdlib.h>

int tilings[35];

void calculateTilings();
int findTileValue(int t);

int main() {
	tilings[2] = 3; // base case, 0 and 1 are both 0
	tilings[4] = 11;
	calculateTilings();
	int length;
	while (1) {
		std::cin >> length;
		if (length == -1) {
			break;
		} else if (length == 0) {
			printf("1\n");
		} else if (length%2 != 0) { // Odd
			printf("0\n");
		} else if (length == 2) {
			printf("3\n");
		} else {
			printf("%d\n", tilings[length]);
		}
	}
/*	for (int k=2; k<33; k++) {
		printf("%d ", tilings[k]);
	}
	putchar('\n');
*/	return 0;
}

void calculateTilings() {
	for (int i=6; i<=34; i=i+2) {
		tilings[i] = findTileValue(i);
	}
}

int findTileValue(int t) {
	return(4*tilings[t-2] - tilings[t-4]);
}
