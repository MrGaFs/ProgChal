#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>

#define INF 1 << 21

using namespace std;

#define MAXE 12*105*105+105 //edges

int start[MAXE];
bool seen[MAXE];

int to[MAXE];
int nextNode[MAXE];
int cap[MAXE];
int cost[MAXE];
int m;
int N;

string grid[105];

void addEdges(int x, int y);
void addEdge(int x, int y, int x1, int y1);
bool inBounds(int x, int y);
bool valid(int x, int y);
bool validPoint(int x, int y);
void add (int u, int v, int ca, int co);
int inv(int e);
int getNode(int x, int y);
int inv(int e);
bool augment(int u, int t, int f);
int max_flow(int s, int t);
void reset();

int main () {
	int cases;
	scanf("%d", &cases);
	for (int c=0; c<cases; c++) {
		scanf("%d\n", &N);	
		reset();
		for (int j=0; j<N; j++) {
			getline(cin, grid[j]);
		}

		for (int j=0; j<N; j++) {
            for (int k=0; k<N; k++) {
				if (grid[j][k] == '#') {
					addEdges(k, j);
					int node = getNode(k, j);
					add(0, node, 1, 1);
					add(node+1, 1, 1, 1);
				}
			}
		}


/*		for (int j=0; j<N; j++) {
            for (int k=0; k<N; k++) {
				printf("%d", grid[j][k]);
			}
			putchar('\n');
		}
*/
		int flow = max_flow(0, 1);
		printf("Case %d: %d\n", c+1, flow/2);
	}
	return 0;
}

bool inBounds(int x, int y) {
    return (x >= 0 && x < N && y >= 0 && y < N);
}
 
bool valid(int x, int y) {
    return (inBounds(x, y) && grid[y][x] == '#');
}

void addEdge(int x, int y, int x1, int y1) {
	int v1 = getNode(x, y);
	int v2 = getNode(x1, y1);
	add(v1, v2+1, 1, 1);
	add(v2, v1+1, 1, 1);
}

void addEdges(int x, int y) {
    if (valid(x+1, y)) {
		addEdge(x, y, x+1, y);
	}
    if (valid(x-1, y)) {
		addEdge(x, y, x-1, y);
	}
    if (valid(x, y+1)) {
		addEdge(x, y, x, y+1);
	}
    if (valid(x, y-1)) {
		addEdge(x, y, x, y-1);
	}
}

int getNode(int x, int y) {
    return 2*(N*y+x+1); // Yay for no overlaps
}

void add (int u, int v, int ca, int co) {
    to[m] = v;
    nextNode[m] = start[u];
    start[u] = m;
    cap[m] = ca;
    cost[m] = co;
    m++;

    // Add reverse edges too
    to[m] = u;
    nextNode[m] = start[v];
    start[v] = m;
    cap[m] = 0;
    cost[m] = -co;
    m++;
}

int inv(int e) {
	return e^1;
}

bool augment(int u, int t, int f) {
	if (u == t) return true;
	if (seen[u]) return false;
	seen[u] = true;
	for (int e = start[u]; ~e; e = nextNode[e]) {
		if (cap[e] >= f && augment(to[e], t, f)) {
			cap[e] -= f;
			cap[inv(e)] += f;
			return true;
		}
	}
	return false;
}

int max_flow(int s, int t) {
	int res = 0;
	memset(seen, 0, sizeof seen);
	while (augment(s, t, 1)) {
		memset(seen, 0, sizeof seen);
		res += 1;
	}
	return res;
}


void reset() {
	for (int i=0; i<N; i++) {
		for (int j=0; j<N; j++) {
			grid[i][j] = 0;
		}
	}
	memset(start, -1, sizeof(start));
	memset(seen, false, sizeof(seen));
	memset(to, 0, sizeof(to));
	memset(nextNode, 0, sizeof(nextNode));
	memset(cap, 0, sizeof(cap));
	m = 0;
}
