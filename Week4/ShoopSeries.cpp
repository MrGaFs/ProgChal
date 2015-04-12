#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define MAX 10005
int XI[MAX]; // forwards
int XD[MAX]; // backwards
int incSub[MAX];
int decSub[MAX];
int inc[MAX];
int dec[MAX];
int length;

void longestIncreasing();
void longestDecreasing();
int calculateMax();
void clear();

int main() {
	while(scanf("%d\n", &length) != EOF) {
		for (int i=0; i<length; i++) {
			int tmp;
			scanf("%d", &tmp);
			XI[i] = tmp;
			XD[length-i-1] = tmp;
		}
		longestIncreasing();
		longestDecreasing();
		int maxS = calculateMax();
		printf("%d\n", maxS+maxS-1);

/*		for (int i=0; i<length; i++) {
			printf("%d ", incSub[i]);
		}
		putchar('\n');
        for (int i=0; i<length; i++) {
            printf("%d ", decSub[i]);
        }
        putchar('\n');



        for (int i=0; i<length; i++) {
            printf("%d ", inc[i]);
        }
        putchar('\n');
        for (int i=0; i<length; i++) {
            printf("%d ", dec[i]);
        }
        putchar('\n');
*/
		clear();
	}
	return 0;
}

void longestIncreasing() {
	int L = 0;
	int P[length+2];
	for (int i = 0; i < length; i++) {
		int lo = 1;
		int hi = L;

		while (lo <= hi) {
			int mid = (lo+hi+1)/2;
			if (XI[incSub[mid]] < XI[i]) { // I think this is right?
				lo = mid+1;
			} else {
				hi = mid-1;
			}
		}

		int newL = lo;
		P[i] = incSub[newL-1];
		if (XI[i] > XI[P[i]]) {
			inc[i] = inc[P[i]]+1;
		} else {
			inc[i] = 1;
		}
		incSub[newL] = i;
		if (newL > L) {
			L = newL;
		}
	}
}

void longestDecreasing() {
	int L = 0;
	int P[length+2];
	for (int i = 0; i < length; i++) {
		int lo = 1;
		int hi = L;

		while (lo <= hi) {
			int mid = (lo+hi+1)/2;
			if (XD[decSub[mid]] < XD[i]) { // I think this is right?
				lo = mid+1;
			} else {
				hi = mid-1;
			}
		}

		int newL = lo;
		P[i] = decSub[newL-1];
		if (XD[i] > XD[P[i]]) {
			dec[i] = dec[P[i]]+1;
		} else {
			dec[i] = 1;
		}
		decSub[newL] = i;
		if (newL > L) {
			L = newL;
		}
	}
}

int calculateMax() {
	int maxI = 0;
	int maxD = 0;
	for (int i=0; i<length; i++) {
		if (inc[i] > maxI) {
			maxI = inc[i];
		}
		if (dec[length-1-i] > maxD) {
			maxD = dec[length-1-i];
		}
	}
	return std::min(maxI, maxD);
}

void clear() {
	for (int i=0; i<length; i++) {
		XI[i] = XD[i] = incSub[i] = decSub[i] = inc[i] = 0;
	}
	length = 0;
}

