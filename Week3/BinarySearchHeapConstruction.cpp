#include <algorithm>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>

struct node {
	char id[200];
	int value;
	int left;
	int right;
	int parent;
};

node nodes[50005];
int n; // number of nodes

void print(int n);
int stringCompare(node a, node b);
int buildTree(int n);

void print_node(node *n) {
	printf("id: %s\tvalue:%d\n", n->id, n->value);
}

int main() {
	scanf("%d", &n);
	putchar(n);
	while (n != 0) {
		for (int i=0; i<n; i++) {
			scanf("%*[ ]%[a-z]/%d", nodes[i].id, &nodes[i].value); // %s kills everything
			nodes[i].right = -1;
			nodes[i].left = -1;
			nodes[i].parent = -1;
		//	print_node(&nodes[i]);
		}
		std::sort(nodes, nodes+n, stringCompare); // Sort all nodes by strings, so they print in order
//		for (int i=0;i<n;i++) {
//			print_node(&nodes[i]);
//		}
		int root = buildTree(n); 
		printf("ALEPH: built tree\n");
		print(root);
		putchar('\n');
		scanf("\n%d", &n);
	}

	return 0;
}

int stringCompare(node a, node b) {
	if (strcmp(a.id, b.id) != 0) { // Different
		return 1;
	} else {
		return 0;
	}
}

void print(int n) {
	putchar('(');
	if (nodes[n].right != -1) {
		print(nodes[n].right);
	}

 	printf("%s/%d", (nodes[n].id), nodes[n].value);

	if (nodes[n].left != -1) {
		print(nodes[n].left);
	}
	putchar(')');
}


int buildTree(int n) {
	std::vector<int> stack;
	stack.push_back(0);

	for (int i=1; i<n; i++) { 
		std::vector<int>::reverse_iterator rit = stack.rbegin();
		while (rit != stack.rend() && nodes[*rit].value < nodes[i].value) { // This is dependent on it being sorted first
			++ rit;
		}
		for (std::vector<int>::const_iterator it = stack.begin(); it != stack.end(); it++) {
			std::cout << *it << ' ';
		}
		putchar('\n');

		int prev = *rit;
		int zero = stack.front(); //stk[0]
		if (1) { // Still children to add
			nodes[i].parent = prev;
			nodes[nodes[prev].right].parent = i;
			nodes[i].left = nodes[prev].right;
			nodes[prev].right = i;
		} else {
			printf("BETH: final value\n");
			nodes[i].left = zero;
			nodes[zero].parent = i;
		}
		stack.push_back(i);
	}
	return stack.front(); // Root value
}
