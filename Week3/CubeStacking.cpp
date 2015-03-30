#include <iostream>
#include <string>
#include <stack>
#include <stdio.h>
#include <stdlib.h>


int parent[30005];
int under[30005];
int elements[30005];

void init(int n);
int Find(int x);
void Union(int x, int y);

int main() {
	for (int j=1; j<30006; j++) {
		parent[j] = j;
		elements[j] = 1;
	}

	int operations;
	scanf("%d\n", &operations);
	for (int i=0; i<operations; i++) {
		char move = getchar();
		if (move == 'M') { // Union
			int start, end;
			scanf(" %d %d\n", &start, &end);
			Union(start, end);
		} else { // Find
			int check;
			scanf(" %d\n", &check);
			Find(check);
			printf("%d\n", under[check]);
		}

    }
	return 0;
}

// Below functions from: http://www.cse.unsw.edu.au/~cs4128/15s1/static/datastructures.pdf

// Thank you stanford
int Find(int x) {
	int temp = parent[x];
	if (x != parent[x]) { // Not the root
		parent[x] = Find(parent[x]); // such recursive
		under[x] = under[temp] + under[x];
	}
	return parent[x];
}

// x is moved onto y
void Union(int x, int y) {
	x = Find(x);
	y = Find(y);
	if (x != y) {
		parent[x] = y;
		under[x] = elements[y] + under[x];
		elements[y] = elements[x] + elements[y];
	}
} 
