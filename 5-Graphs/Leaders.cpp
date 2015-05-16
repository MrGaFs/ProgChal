#include <stdlib.h>
#include <stdio.h>
#include <stack>
#include <vector>

struct adj {
	std::vector<int> n; // neighbours
};

int parent[100005];
adj adjacent[100005];
int visited[100005];

void unionSet(int x, int y);
int findSet(int x);
bool isOddPath(int a, int b, int c);

int main() {
	int vertices, edges;
	scanf("%d %d", &vertices, &edges);
	for (int i=1; i<=vertices; i++) {
		parent[i] = i;
	}

	// Construct our graph
	for (int i=0; i<edges; i++) {
		int a,b;
		scanf("%d %d", &a, &b);
		if (findSet(a) != findSet(b)) { // new tree
			unionSet(a, b);
		}
		(adjacent[a].n).push_back(b);
		(adjacent[b].n).push_back(a);
	}

	// Find answers
	// If findSet is different, absolutely not
	// Else, calculate length of possible paths
	int questions;
	scanf("%d", &questions);
	for (int i=0; i<questions; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		if (findSet(a) != findSet(b)) {
			printf("No\n");
		} else {
			bool odd = isOddPath(a, b, 0);
			if (odd == true) {
				printf("Yes\n");
			} else {
				printf("No\n");
			}
		}

	}
	return 0;
}

std::stack<int> st;

bool isOddPath(int a, int b, int c) {
	while(!st.empty()) {
		for (unsigned int i=0; i<(adjacent[a].n).size(); i++) {
			if (visited[(adjacent[a].n)[i]] == 0) { // new node
				st.push((adjacent[a].n)[i]);
			}
		}
		int tmp = st.top();
		st.pop();
		visited[tmp] = 1;
		if (tmp == b && c%2 == 1) { // We have an odd path
			return true;
		}
		isOddPath(tmp, b, c+1);
	}
	return false;
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
