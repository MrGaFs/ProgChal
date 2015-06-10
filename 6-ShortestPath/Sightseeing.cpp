#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <algorithm>

#define MAX 10000
#define INF 1 << 30

struct edge {
	int to;
	int w;
};

int parent[MAX];
int seen[MAX];
std::vector<edge> roads[MAX]; // array of vectors, no saving those starts

void reset(int roads);
void ffloyd_warshall(int n);

int main() {
	int cases;
	scanf("%d", &cases);
	for (int c=0; c<cases; c++) {
		int cities, roads;
		scanf("%d %d", &cities, &roads);
		for (int r=0; r<roads; r++) {
			edge tmp;
			int s;
			scanf("%d %d %d", &s, &tmp.to, &tmp.w);
			roads.push_back(tmp);
		}
		int start, end;
		scanf("%d %d", &start, &end);
		ffloyd_warshall(roads);
		reset(roads);
	}
	return 0;
}

void reset(int roads) {
	roads.clear();
	for (int i=0; i<roads; i++) {
		for (int j=0; j<roads; j++) {
			dist[i][j] = INF;
		}
	}
}

void djikstras (edge start) {
	priority_queue<edge, vector<edge>, greater<edge> > pq;
	push(start);
	while (!pq.empty()) {
		edge cur = pq.top();
		pq.pop();
		int s = cur.s;
		int e = cur.e;
		int w = cur.w;
		if (seen[s] == 1) {
			continue;
		} else {
			dist[e] = dist[s] + w;
			seen[e] = 1;
		}
		for (unsinged int i=0; i<roads.size(); i++) {
			if (roads[i].s == e) { // connector
				if (seen[roads[i].s] == 0) {
					pq.push(roads[i]);
				}
			}
		}
	}
}
