#include <stdlib.h>
#include <stdio.h>
#include <cmath>

struct stones {
	int x;
	int y;
};

stones loc[205];
int visited[205];
float edge[205][205]; // Stores distances
float dict[205];

void reset(int stone);
float max(float a, float b);
float calculateEdge(int u, int v);
void calculateDistance(int stone);


int main() {
	int scenario = 1;
	int stone;
	scanf("%d", &stone);
	while(stone != 0) {
		reset(stone);
		for (int i=0; i<stone; i++) { //Remember: Fred = [0], Fiona = [1]
			int x, y;
			scanf("%d %d", &x, &y);
			loc[i].x = x;
			loc[i].y = y;
		}

		// Calculate every possible jump
		for (int i=0 ; i<stone; i++) {
			for (int j=0; j<stone; j++) {
				edge[i][j] = edge[j][i] = calculateEdge(i, j);
			}
		}

/*		for  (int i=0 ; i<stone; i++) {
            for (int j=0; j<stone; j++) {
				printf("%f ", edge[i][j]);
			}
			printf("\n");
		}
*/
		printf("Scenario #%d\n", scenario);
		scenario ++;

		// Find the minimum distance (Djikstra's)
		calculateDistance(stone);
/*		for (int i=0; i<stone; i++) {
			printf("%f ", dict[i]);
		}
		printf("\n");
*/
		printf("Frog Distance = %0.3f\n\n", dict[1]);

		scanf("%d", &stone);
	}
	return 0;
}

void reset(int stone) {
	for (int i=0; i<=stone; i++) {
		visited[i] = 0;
		dict[i+1] = 999999; // If 0, Fred is eternally away
		for(int j=0; j<=stone; j++) {
			edge[i][j] = 0;
		}
	}
}

float max(float a, float b) {
	if (a > b) {
		return a;
	} else {
		return b;
	}
}

float calculateEdge(int u, int v) {
	float dx = loc[u].x - loc[v].x;
	float dy = loc[u].y - loc[v].y;
	return (sqrt(dx*dx + dy*dy));
}

void calculateDistance(int stone) {
	int current = 0;
	for (int i=0; i<stone; i++) {
		int k;
		float min = 999999;
		for (int j=1; j<stone; j++) {
			if (visited[j] == 0) {
				float maxi = max(dict[current], edge[j][current]);
//				printf("max: %f\n", maxi);
				if (dict[j] > maxi) {
					dict[j] = maxi;
				}
				if (min > dict[j]) {
					min = dict[j];
					k = j;
				}
			}
		}
		if (k == 1) { // Found Fiona
			return;
		}
		current = k;
		visited[k] = 1;
	}
}
