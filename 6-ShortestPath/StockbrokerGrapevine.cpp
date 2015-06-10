#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <utility>
#include <queue>

using namespace std;

typedef pair<int, int> edge;

const int MAX = 105;
const int inf = 99999;

std::vector<edge> links[MAX];
bool seen[MAX];
int dist[MAX];

void reset(int brokers);
void djikstras(int start);
void calculateGreatest(int brokers);

int main () {
	int brokers;
	scanf("%d", &brokers);
	while(brokers != 0) {
		for (int i=1; i<=brokers; i++) {
			int connections;
			scanf("%d", &connections);
			for (int j=0; j<connections; j++) {
				edge tmp;
				scanf("%d %d", &tmp.second, &tmp.first);
				links[i].push_back(tmp);
			}
		}
		calculateGreatest(brokers);
		reset(brokers);
		scanf("%d", &brokers);
	}
	return 0;
}

void calculateGreatest(int brokers) {
	int bestTime = inf;
	int bestBroker = 0;
	for (int i=1; i<=brokers; i++) {
		djikstras(i);
//		for (int j=1; j<=brokers; j++) {
//			printf("%d ", dist[j]);
//		}
//		printf("\n");
		int greatest = 0;
		for (int j=1; j<=brokers; j++) {
			if (i == j) {
				continue;
			} else if (dist[j] > greatest) {
				greatest = dist[j];
			}
		}
		if (greatest < bestTime) {
			bestTime = greatest;
			bestBroker = i;
		}
		for (int j=0; j<=brokers; j++) {
			seen[j] = false;
			dist[j] = inf;
		}
	}
	if (bestTime == inf) {
		printf("disjoint\n");
	} else {
		printf("%d %d\n", bestBroker, bestTime);
	}
}

void djikstras(int start) {
	priority_queue<edge, vector<edge>, greater<edge> > pq;
	pq.push(edge(0, start));
	while (!pq.empty()) {
		edge cur = pq.top();
		pq.pop();
		int v = cur.second;
		int d = cur.first;
		if (seen[v]) {
			continue;
		}
		dist[v] = d;
		seen[v] = true;
		for (unsigned int i=0; i<links[v].size(); i++) {
			edge next = links[v][i];
			int u = next.second;
			int nextD = next.first;
			if (!seen[u]) {
				pq.push(edge((d+nextD), u));
			}
		}
	}
}

void reset(int brokers) {
	for(int i=0; i<=brokers; i++) {
		links[i].clear();
		seen[i] = false;
		dist[i] = inf;
	}
}
