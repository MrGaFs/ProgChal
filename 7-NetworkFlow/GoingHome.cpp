#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <utility>

#define INF 1 << 21

using namespace std;

struct point {
	int x;
	int y;
};

#define MAX 2*105*105+4*105

point houses[105];
int H=0;
point men[105];
int M=0;

int to[MAX];
int from[MAX];
int parent[MAX];
int cap[MAX];
int cost[MAX];
int dist[MAX]; 
int m=0;

int X, Y;

void setUp();
int manhattanDistance(point a, point b);
int findHouse(int a);
int findMan(int a);
void add (int u, int v, int ca, int co);
int inv(int e);
pair<int, int> mincostmaxflow(int s, int t);

int main () {
	scanf("%d %d", &Y, &X);
	while (X != 0 && Y != 0) {
		setUp();
		for (int y=0; y<X; y++) {
			char c;
			scanf("%c", &c);
			for (int x=0; x<Y; x++) {
				scanf("%c", &c);
				if (c == 'H') {
					houses[H].x = x;
					houses[H].y = y;
					H ++;
				} else if (c == 'm') {
					men[M].x = x;
					men[M].y = y;
					M ++;
				}
			}
		}
		for (int i=0; i<M; i++) {
			add(0, findMan(i), 1, 0);
		}
		for (int i=0; i<H; i++) {
			add(findHouse(i), 1, 1, 0);
		}


		// Calculate all the edge costs and add them
		for (int i=0; i<H; i++) {
			for (int j=0; j<M; j++) {
				add(findMan(j), findHouse(i), 1, manhattanDistance(houses[i], men[j]));
			}
		}

/*		for (int i=0; i<m; i++) {
			printf("%d->%d: %d %d\n", from[i], to[i], cap[i], cost[i]);
		}
*/
		pair<int, int> flow = mincostmaxflow(0, 1);
		printf("%d\n", flow.second);

		scanf("%d %d", &X, &Y);
	}
	return 0;
}

void setUp() {
	memset(parent, -1, sizeof(parent));
	m = H = M = 0;
}

int manhattanDistance(point a, point b) {
	return abs(a.x-b.x) + abs(a.y-b.y);
}

int findHouse(int a) {
    return a+2;
}

int findMan(int a) {
    return a+2+H;
}


void add (int u, int v, int ca, int co) {
    to[m] = v;
    from[m] = u;
    cap[m] = ca;
    cost[m] = co;
    m++;

    // Add reverse edges too
    to[m] = u;
    from[m] = v;
    cap[m] = 0;
    cost[m] = -co;
    m++;
}

int inv(int e) {
	return e^1;
}

pair<int, int> mincostmaxflow(int s, int t) {
	int total_flow = 0, total_cost = 0;
	while (true) {
		for (int i = 0; i < m; i++) {
			dist[i] = INF;
		}
		dist[s] = 0;
		parent[s] = -1;
		// use bellman-ford to find a shortest augmenting path
		bool updated = true;
		while (updated) {
			updated = false;
			for (int e = 0; e < m; e++) {
				if (cap[e] > 0) {
					int u = from[e], v = to[e];
					if (dist[u] + cost[e] < dist[v]) {
						dist[v] = dist[u] + cost[e];
						parent[v] = e;
						updated = true;
					}
				}
			}
		}
		// if we didn't find any augmenting paths, break
		if (dist[t] == INF) {
			break;
		}
		// push the unit of flow through the shortest augmenting path found
		total_flow ++;
		total_cost += dist[t];
		// move along the shortest augmenting path found and maintain the residual graph

		for (int e = parent[t]; ~e; e = parent[from[e]]) {
			cap[e]--;
			cap[inv(e)]++;
		}
	}
	return make_pair(total_flow, total_cost);
}
