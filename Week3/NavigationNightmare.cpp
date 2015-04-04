#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int manhattanDistance (int x1, int x2, int y1, int y2);

typedef struct {
	int x; 
	int y;
} *Farm;

typedef struct {
	int x;
	int y;
	int f1;
	int f2;
} *Road;

typedef struct {
	int f1;
	int f2;
	int line;
} *Quest;

Farm farms[40005];
Road roads[40005]
Quest query[10005];


int main() {
	// Remember, S and W mean -ve numbers

	// Initialise the elements
	for (int i=0; i<40005; i++) {
		farms[i]->x = 0;
		farms[i]->y = 0;
	}

	int N, M;
	scanf("%d %d\n", &N, &M);

	// Get the inputs
	for (int j=0; j<M; j++) {
		int size;
		char dir;
		scanf("%d %d %d %c\n", &road[i]->f1, &road[i]->f2, &size, &dir)
		int x = 0;
		int y = 0;
		if (dir == 'N') {
			y = len;
		} else if (dir == 'S') {
			y = -len;
		} else if (dir == 'E') {
			x = len;
		} else if (dir == 'W') {
			x = -len;
		}
		road[i]->x = x;
		road[i]->y = y;
	}

	int Q;
	scanf("%d\n", &Q);

	// Get the questions
	for (int k=0; k<Q; k++) {
		int f1, f2, line;
		scanf("%d %d %d\n", &f1, &f2, &line);

	}

	return 0;
}


int manhattanDistance (int x1, int x2, int y1, int y2) {
	return abs(x1-x2) + abs(y1-y2);
}
