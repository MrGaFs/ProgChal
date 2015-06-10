#include <stdio.h>
#include <stdlib.h>
#include <iostream>

int findMax(int a, int b);

int triangle[105][105];
int maxVal[105][105];

int main() {
	int n;
	scanf("%d\n\n", &n);
	for (int i=1; i<=n; i++) {
		for (int j=0; j<i; j++) {
			int c;
			std::cin >> c;
			getchar(); // gets space or \n
			triangle[i-1][j] = c; // Can only access below and to the right
		}
	}

	maxVal[0][0] = triangle[0][0];

	for(int k=1; k<=n; k++) {
		for(int l=0; l<k; l++) {
			if (l == 0) { // left edge, only one option
				maxVal[k-1][l] = triangle[k-1][l] + maxVal[k-2][l];
			} else if (l == k-1) { // right edge, only one option
				maxVal[k-1][l] = triangle[k-1][l] + maxVal[k-2][l-1];
			} else {
				int a = triangle[k-1][l] + maxVal[k-2][l];
				int b = triangle[k-1][l] + maxVal[k-2][l-1];
				maxVal[k-1][l] = findMax(a, b);
			}
		}
	}

	int max = 0;
	for(int m=0; m<n; m++) {
		if (maxVal[n-1][m] > max) {
			max = maxVal[n-1][m];
		}
	}

	printf("%d\n", max);

	return 0;
}

int findMax(int a, int b) {
	if (a > b) {
		return a;
	} else {
		return b;
	}
}
