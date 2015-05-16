#include <cstdlib>
#include <stdio.h>
#include <vector> 
#include <set>
#include <queue>
#include <algorithm>

using namespace std;
 
// Who the fuck named this shit
#define MAX 10010
#define INF 1 << 30
struct edge {
    int to, from, w;
};
 
int N, ML, MD;
vector<edge> edges;
int dist[MAX];
int parent[MAX];
bool neg;

void relax (int u, int v, int w);
void initialise (int start);
int bellman_ford (int start, int end);
bool sorter(edge a, edge b);
 
int main () {
    neg = false;
    scanf("%d %d %d", &N, &ML, &MD);
    for (int i=0; i<ML; i++) {
        edge tmp;
        scanf("%d %d %d", &tmp.to, &tmp.from, &tmp.w);
        edges.push_back(tmp);   
    }
    for (int i=0; i<MD; i++) {
        edge tmp;
        scanf("%d %d %d", &tmp.from, &tmp.to, &tmp.w);
        tmp.w = -(tmp.w);
        edges.push_back(tmp);
    }
	int bellman = bellman_ford(1, N);
	if (bellman == -1) {
		printf("-1\n");
	} else {
		if (dist[N] == INF) {
			printf("-2\n");
		} else {
			printf("%d\n", dist[N]);
		}
	}

//	for (int i=1; i<=N; i++) {
//		printf("%d: %d %d\n", i, dist[i], parent[i]);
//	}

	return 0;
}

// Bellman Ford, taken from lecture notes for dartmouth university

/* Initialize a single-source shortest-path computation */
void initialise (int start) {
	for (int i=0; i<= N; i++) {
		dist[i] = INF;
		parent[i] = -1;
	}
	dist[start] = 0;
}

/* Run the Bellman-Ford algorithm from vertex s.  Fills in arrays d
   and parent. */
int bellman_ford (int start, int end) {
	initialise(start);

	// relax every edge
	for (int a=0; a<N; a++) {
		for (unsigned int i=0; i<edges.size(); i++) {
			edge curr = edges[i];
			if (dist[curr.to] + curr.w < dist[curr.from]) {
				dist[curr.from] = dist[curr.to] + curr.w;
				parent[curr.from] = curr.to;
			}
		}
	}

	// Check for negative loops
	for (unsigned int i=0; i<edges.size(); i++) {
		if (dist[edges[i].from] > dist[edges[i].to] + edges[i].w) {
			return -1; // negative loop
		}
	}
	return 1;
}

bool sorter(edge a, edge b) {
	return a.from<b.from;
}
