#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>

// Make thee a union set for great good.
// Prog Chal textbook is pretty ace

int parent[200];
int visited[200];
int isTree;

void cleanup();
int findSet(int x);
void unionSet(int x, int y);

int main() {
	cleanup();
	int tmp = 0;
	int a, b;
	int cases = 0;
	scanf("%d %d", &a, &b);
	while (a != -1 && b!= -1) {
		if (a == 0 && b == 0) {
			// Check for forests
			for (int i=1; i<200; i++) {
				if (visited[i] == 1 && findSet(i) != findSet(tmp)) { 
					isTree =  1;
				}
			}
			cases ++;
			if (isTree == 0) {
				printf("Case %d is a tree.\n", cases);
			} else {
                printf("Case %d is not a tree.\n", cases);
			}
			cleanup();
		} else {
			visited[a] = visited[b] = 1;
			tmp = a;
			if (a == b) { // Loop
				isTree = 1;
			}
			// Already in the same set, so part of a loop
			if (findSet(a) == findSet(b)) {
				isTree = 1;
			}
			unionSet(a, b);

		}
		scanf("%d %d", &a, &b);
	}
	return 0;
}

void unionSet(int x, int y) {
	x = findSet(x);
	y = findSet(y);
	if (x != y) {
		parent[y] = x;
	}
}

int findSet(int x) {
	if (x != parent[x]) {
		parent[x] = findSet(parent[x]);
	}
	return parent[x];
}

void cleanup() {
	isTree = 0;
	for (int i=0; i<201; i++) {
		visited[i] = 0;
		parent[i] = i;
	}
}
