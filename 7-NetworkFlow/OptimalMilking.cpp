#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <utility>

#define INF 1 << 21

using namespace std;

#define MAX 4*250+2*35+2*205

int to[MAX];
int from[MAX];
int parent[MAX];
int cap[MAX];
int cost[MAX];
int dist[MAX]; 
int distances[250][250];
int m=0;

int K, C, M;// K = Machines
			// M = Capcity
			// C = Cows

int findMilk(int a);
void floydWarshall();
void add (int u, int v, int ca, int co);
int inv(int e);
pair<int, int> mincostmaxflow(int s, int t);

int main () {
	scanf("%d %d %d", &K, &C, &M);
	memset(parent, -1, sizeof(parent));
	
	for (int i=0; i<C; i++) {
		add(0, findMilk(i+K), 1, 0);
	}
	for (int i=0; i<K; i++) {
		add(findMilk(i), 1, M, 0);
	}


	// Read in inputs and make edges
	for (int r=0; r<K+C; r++) { // row
		for (int c=0; c<K+C; c++) { // column
			int tmp;
			scanf("%d", &tmp);
			if (tmp != 0) {
				distances[r][c] = tmp;
			} else {
				distances[r][c] = INF;
			}
		}
	}

	// Run Floyd-Warshall
	floydWarshall();

/*	for (int r=0; r<K+C; r++) { // row
   		for (int c=0; c<K+C; c++) { // column
			printf("%d", distances[r][c]);
		}
		putchar('\n');
	}
*/
	// Make the graph on the basis of the results
	for (int i=0; i<K+C; i++) {
		for (int j=0; j<K+C; j++) {
			int c = distances[i][j];
			if (c != 0) {
				if (i<K && j<K) { // machine to machine
//	                add(findMilk(i), findMilk(j), C, c);
				} else if (i>K && j>K) { // cow to cow
//                    add(findMilk(i), findMilk(j), C, c);
				} else {
					add(findMilk(i), findMilk(j), 1, c);
				}
			}
		}
	}

	pair<int, int> flow = mincostmaxflow(0, 1);
	printf("%d\n", flow.second);
	return 0;
}

int findMilk(int a) {
    return a+2;
}

void floydWarshall() {
	for (int k=0; k<K+C; k++) {
		for (int i=0; i<K+C; i++) {
			for (int j=0; j<K+C; j++) {
				if (distances[i][j] > distances[i][k]+distances[k][j]) {
					distances[i][j] = distances[i][k]+distances[k][j];
				}
			}
		}
	}
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
	int total_flow = 0, max_cost = 0;
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
		if (dist[t] > max_cost) {
			max_cost = dist[t];
		}

		// move along the shortest augmenting path found and maintain the residual graph

		for (int e = parent[t]; ~e; e = parent[from[e]]) {
			cap[e]--;
			cap[inv(e)]++;
		}
	}
	return make_pair(total_flow, max_cost);
}
