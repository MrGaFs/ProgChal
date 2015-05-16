#include <algorithm>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

struct node {
	int value; // Use this value to access the id in strings
	int index;
	int left;
	int right;
	int parent;
};

char strings[50005][100];
node nodes[50005];

int n; // number of nodes

void print(int n);
void addNode(int index);
int stringCompare(int a, int b);

int main() {
	scanf("%d", &n);
	putchar(n);
	while (n != 0) {
		int tmpLoc[n+1];
		int tmpVal[n+1];
		for (int i=1; i<n+1; i++) {
			int x;
			scanf("%*[ ]%[a-z]/%d", strings[i], &x); // %s kills everything
			tmpVal[i] = x;
			tmpLoc[i] = i;
			nodes[i].right = 0;
			nodes[i].left = 0;
			nodes[i].parent = 0;
			nodes[i].index = i;
		}
		// Do stuff here to print the monstrosity
		nodes[0].value = 9999999; // Large enough not to be an issue
		nodes[0].parent = 0;
		nodes[0].left = 0;
		nodes[0].right = 0;

		// Sort by string for heap like deliciousness
		std::sort(tmpVal+1, tmpVal+1+n, stringCompare);

		for(int j=1; j<n+1; j++) {
			nodes[j].value = tmpVal[tmpLoc[j]];
			nodes[j].index = tmpLoc[j];
		}

		for (int k=1; k<n+1; k++) {
			addNode(k);
		}
		print(nodes[0].right);
		scanf("\n%d", &n);
	}

	return 0;
}

int stringCompare(int a, int b) {
	return strcmp(strings[a], strings[b]) < 0;
}

void print(int n) { // Rewrite
	if (n == 0) {
		return;
	} else {
		putchar('(');
		if (nodes[n].right != 0) {
			print(nodes[n].right);
		}
	
	 	printf("%s/%d", (strings[nodes[n].index]), nodes[n].value);
	
		if (nodes[n].left != 0) {
			print(nodes[n].left);
		}
		putchar(')');
	}
}

void addNode (int index) {
	int parent = index-1;
	while (nodes[parent].value < nodes[index].value) {
		int p = nodes[p].parent;
	}
	nodes[index].parent = parent;
	nodes[index].left = nodes[parent].right;
	nodes[parent].right = index;
}

