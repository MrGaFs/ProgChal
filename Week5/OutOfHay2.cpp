#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <algorithm>

struct edge {
	int u, v, w;
}; 

int farms, roads;
edge edges[10010];
int p[10010];

int mst(int m);
void join(int u, int v);
int root (int u);
int srt(edge a, edge b);

int main () {
	scanf("%d %d", &farms, &roads);
	for (int i=0; i<roads; i++) {
		scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
	}

	if (roads < 2) {
		printf("%d\n", edges[0].w);
	} else {
		std::sort(edges, edges+roads, srt);

		for (int i=0; i<roads; i++) {
    	    p[i] = i; // Setup for union-find
		}

//	for (int i=0; i<roads; i++) {
//		printf("%d->%d: %d, p: %d\n", edges[i].u, edges[i].v, edges[i].w, p[i]);
//	}
		int totalWeight = mst(roads);
		printf("%d\n", totalWeight);
	}
		return 0;
}

// All helper functions taken from lecture notes
void join(int u, int v) {
	u = root(u);
	v = root(v);
	p[u] = v;
}

int root(int u) { // Here is where we are segfaulting
	return u == p[u] ? u : p[u] = root(p[u]);
}

int mst(int m) {
	int greatest_weight = 0;
	for (int i = 0; i < m; i++) {
		if (root(edges[i].v) != root(edges[i].u)) {
			if (edges[i].w > greatest_weight) {
				greatest_weight = edges[i].w;
			}
			join(edges[i].v, edges[i].u);
		}
	}
	return greatest_weight;
}

int srt(edge a, edge b) {
	return a.w < b.w;
}
