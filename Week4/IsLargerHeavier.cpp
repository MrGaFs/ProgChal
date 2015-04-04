#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <stack>

struct info {
	int weight;
	int size;
	int num;
};

void longestDecreasingSubsequence(int len);
bool compareSize(info a, info b);

info parcels[1005];

int main() {
	int i=1;
	int s,w;
	while (scanf("%d %d\n", &s, &w) != EOF) {
		parcels[i].weight = w;
		parcels[i].size = s;
		parcels[i].num = i;
		i++;
	}

	if (i == 1) {
		printf("1\n1\n");
	} else {
		// sort 
		std::stable_sort(parcels+1, parcels+i, compareSize);

/*		printf("Index	Weight	Size	Num\n");
		for(int j=1; j<i; j++) {
			printf("%d	%d	%d	%d\n", j, parcels[j].weight, parcels[j].size, parcels[j].num);
		}
*/
		longestDecreasingSubsequence(i);

	}
	return 0;
}

bool compareSize(info a, info b) {
	return(a.size < b.size);
}

// By weight, because size is already sorted
void longestDecreasingSubsequence(int len) {
	int previous[len];
	int length[len];
	for(int i=1; i<len; i++) {
		previous[i] = -1;
		length[i] = 1;
	}

	int bestIndex;
	int bestLength;

	for (int curr=1; curr<len; curr++) {
		for (int prev=1; prev<curr; prev++) {
			if (parcels[prev].weight > parcels[curr].weight &&
				parcels[prev].size < parcels[curr].size) { // previous memember
					if (length[prev]+1 > length[curr]) {
						length[curr] = length[prev]+1;
						previous[curr] = prev;
						if (length[curr] > bestLength) {
							bestLength = length[curr];
							bestIndex = curr;
						}
					}
			}
		}	
	}


	std::stack<int> toPrint;
	int curr = bestIndex;
	while (previous[curr] != -1) {
		toPrint.push(parcels[curr].num);
		curr = previous[curr];
	}
	toPrint.push(parcels[curr].num);

	std::cout << toPrint.size() << '\n';
	while (!toPrint.empty()) {
		std::cout << toPrint.top() << '\n';
		toPrint.pop();
	}

/*	printf("Index	Prev	Length\n");
	for(int l=1; l<len; l++) {
		printf("%d	%d	%d\n", l, previous[l], length[l]);
	} */
}

