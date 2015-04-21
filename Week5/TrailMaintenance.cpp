#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <vector>

#define MAX 6005

struct node {
	int start;
	int end;
	int weight;
};

std::vector<node> links;
int parent[MAX];

void unionSet(int x, int y);
int findSet(int x);
void setup();
bool sorter(node x, node y);
int mst(int edges);

unsigned int nodes; // Nodes

int main () {
	int cases;
	scanf("%d", &cases);
	for (int c=1; c<cases+1; c++) {
		printf("Case %d:\n", c);
		nodes = 0;
		int W;
		scanf("%d %d", &nodes, &W);

		for (int i=0; i<W; i++) {
			setup();
			node curr;
			scanf("%d %d %d", &curr.start, &curr.end, &curr.weight);
			links.push_back(curr);
			printf("%d\n", mst(i+1));
		}
		// reset edges TODO: Remove edges
		links.clear();
	}
	return 0;
}

int mst(int edges) {
	if (links.size() < nodes-1) {
		return -1;
	} else {
		std::sort(links.begin(), links.end(), sorter);
		int totalW = 0;
		std::vector<node> mstEdges;
		for (unsigned int i=0; i<links.size(); i++) {
			if (findSet(links[i].start) != findSet(links[i].end)) {
				totalW += links[i].weight;
				unionSet(links[i].start, links[i].end);
				mstEdges.push_back(links[i]);
			}
		}
		if (mstEdges.size() < nodes-1) {
			return -1;
		}
		links = mstEdges;
		return totalW;
	}
}

void setup() {
	for (unsigned int i=0; i<=nodes; i++) {
		parent[i] = i;
	}
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

bool sorter(node x, node y) {
	return x.weight<y.weight;
}
