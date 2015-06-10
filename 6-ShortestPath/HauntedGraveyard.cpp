#include <cstdlib>
#include <stdio.h>
#include <vector>
#include <algorithm>

#define MAX 1000
#define INF 1 << 30

using namespace std;

int W, H;

struct edge {
    int u, v, w;
};

vector<edge> edges;
int loc[MAX]; 	// sures where non-grass squares are
				// 1 = grave
				// 2 = portal
int dist[MAX];
int parent[MAX];
bool seen[MAX];

void create_graph ();
void addEdge(int x1, int y1, int x2, int y2, int w);
bool isValid (int x, int y);
void initialise (int start);
bool relax();
bool bellman_ford (int start, int end);
void reset();

int main () {
	scanf("%d %d", &W, &H);
	while (W != 0 && H != 0) {
		// Read in graves
		int G;
		scanf("%d", &G);
		for (int i=0; i<G; i++) {
			int X, Y;
			scanf("%d %d", &X, &Y);
			int place = (Y)*W+(X);
			loc[place] = 1;
		}
		// Read in portals
		int E;
		scanf("%d", &E);
		for (int i=0; i<E; i++) {
			int X1, Y1, X2, Y2, T;
			scanf("%d %d %d %d %d", &X1, &Y1, &X2, &Y2, &T);
			int place = (Y1)*W+(X1);
			loc[place] = 2;
			edge tmp;
			tmp.u = (Y1)*W+(X1);
			tmp.v = (Y2)*W+(X2);
			tmp.w = T;
			edges.push_back(tmp);
		}
		// Add other edges
		create_graph();

		bool V = bellman_ford(0, W*H-1);
//		printf("edges: %lu\n", edges.size());
		if (V == false) {
			printf("Never\n");
		} else { 
			if (dist[W*H-1] == INF || seen[W*H-1] == false) {

				printf("Impossible\n");
			} else {
/*				for (int y=H-1; y>=0; y--) {
					for (int x=0; x<W; x++) {
						int dis = dist[(y)*W+(x)];
						if (dis == INF) {
							printf("INF ");
						} else {
							printf("%d ", dis);
						}
						
//						printf("%d ", loc[(y)*W+(x)]);
					}
					putchar('\n');
				}
*/				printf("%d\n", dist[W*H-1]);
			}
		}
		scanf("%d %d", &W, &H);
		reset();
	}
	return 0;
}

void create_graph () {
	for (int x=0; x<W; x++) {
		for (int y=0; y<H; y++) {
			if (x*y != W*H-1 && loc[y*W+x] == 0) {
				// go right
				addEdge(x, y, x+1, y, 1);
				// go up
				addEdge(x, y, x, y+1, 1);
				// go left
				addEdge(x, y, x-1, y, 1);
				// go down
				addEdge(x, y, x, y-1, 1);
			}
		}
	}
}

void addEdge(int x1, int y1, int x2, int y2, int w) {
	if (isValid(x1, y1) == true && isValid(x2, y2) == true) {
		if (x1 != W-1 || y1 != H-1) {
			edge tmp;
			tmp.u = (y1)*W+(x1);
			tmp.v = y2*W+x2;
			tmp.w = w;
			edges.push_back(tmp);
		}
	}
}

bool isValid (int x, int y) {
	if ((x >= 0 && x < W) && (y >= 0 && y < H)) {
		if (loc[(y)*W+(x)] != 1) {
			return true;
		}
	}
	return false;
}

// Bellman Ford, taken from lecture notes for dartmouth university

/* Initialize a single-source shortest-path computation */
void initialise (int start) {
    for (int i=0; i<= W*H; i++) {
        dist[i] = INF;
        parent[i] = -1;
		seen[i] = false;
    }
    dist[start] = 0;
	seen[start] = true;
}

bool relax() {
	bool check = false;
	for (unsigned int i=0; i<edges.size(); i++) {
        edge curr = edges[i];
        if (dist[curr.u] + curr.w < dist[curr.v]) {
            dist[curr.v] = dist[curr.u] + curr.w;
            parent[curr.v] = curr.u;
			check = true;
        }
        if (seen[curr.u] == true) {
            seen[curr.v] = true;
        }
    }
	return check;
}

/* Run the Bellman-Ford algorithm v vertex s.  Fills in arrays d
   and parent. */
bool bellman_ford (int start, int end) {
    initialise(start);
    // relax every edge
    for (unsigned int a=0; a<edges.size(); a++) { 
		if (relax() == false) {
			break;
		}
    }

    // Check for negative loops
    for (unsigned int i=0; i<edges.size(); i++) {
        if (dist[edges[i].v] > dist[edges[i].u] + edges[i].w) {
			if (seen[edges[i].v] == true) {
            	return false; // negative loop
			}
        }
    }
    return true;
}

void reset() {
	edges.clear();
	for (int i=0; i<MAX; i++) {
		loc[i] = 0;
	}
}
