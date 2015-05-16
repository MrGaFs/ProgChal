#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <stack>

int seen[5005];
int preorder[5005];
int low[5005];
int degree[5005];

int connections[5005][5005], m;
int t;
int f, r;

void findBridges(int u, int from);

int main() {
	scanf("%d %d", &f, &r);
	if (f == 1) {
		printf("0\n");
	} else {
		m = 0;
		t = 0;
		memset(preorder, -1, sizeof(preorder));
		for (int i=0; i<r; i++) {
			int a, b;
			scanf("%d %d", &a, &b);
			connections[a][b] = connections[a][b] + 1;
			connections[b][a] = connections[b][a] + 1;
		}

/*		for(int i=0; i<f; i++) {
			for (int j=0; j<f; j++) {
				printf("%d ", connections[i+1][j+1]);
			}
			putchar('\n');
		}
*/
		findBridges(1, -1);


		for (int i=1; i<=f; i++) {
			for (int j=1; j<=f; j++) {
				int conn = connections[i][j];
				if (conn > 0 && low[i] != low[j]) { // bridge is here
					degree[low[i]] ++;
				}
			}
		}

		int isolated = 0;

		for (int i=0; i<f; i++) {
			if (degree[i] == 1) {
				isolated ++;
			}
		}

		printf("%d\n", (isolated+1)/2);

	}
	return 0;
}


void findBridges(int u, int from) {
	preorder[u] = t++;
	low[u] = preorder[u];
	for (int i=1; i<=f; i++) {
		int v=0;
		if (connections[i][u] > 0) {
			v = i;
		} else {
			continue;
		}

		// ignore the edge to our parent in the findBridges
		if (v == from) continue;
		// update the lowest value in the preorder sequence that we can reach
		if (preorder[v] != -1) {
			low[u] = std::min(low[u], preorder[v]);
		} else {
			findBridges(v, u);
			low[u] = std::min(low[u], low[v]);
		}
	}
} 
