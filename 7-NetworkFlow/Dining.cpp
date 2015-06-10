#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <queue>

#define INF 1 << 21

using namespace std;

const int MAXN = 105; // cows
const int MAXK = 205; // Food + drinks
const int MAXE = 300*2+100*100*100; //edges

int start[MAXK*2+2+MAXN];
bool seen[MAXK*2+2+MAXN];

int to[MAXE];
int next[MAXE];
int cap[MAXE];
int cost[MAXE];
int m;
int N;
int F;
int D; 

void add (int u, int v, int ca, int co);
int inv(int e);
int getFood(int a);
int getCowFood(int a);
int getDrink(int a);
int getCowDrink(int a);
void setupTheThings();
int inv(int e);
bool augment(int u, int t, int f);
int max_flow(int s, int t);

int main () {
    scanf("%d %d %d", &N, &F, &D);
    setupTheThings();
    for (int cow=1; cow<=N; cow++) {
        int f,d;
        scanf("%d %d", &f, &d);
		for (int j=0; j<f; j++) {
			int food;
			scanf("%d", &food);
			add (getFood(food), getCowFood(cow), 1, 1); // food to cow
		}
		for (int k=0; k<d; k++) {
			int drink;
			scanf("%d", &drink);
			add (getCowDrink(cow), getDrink(drink), 1, 1); // cow to drink
		}
    }
	int flow = max_flow(0, 1);
    printf("%d\n", flow);
    return 0;
}

void setupTheThings() {
	memset(start, -1, sizeof(start));

	// Cow to cow
	for (int i=1; i<=N; i++) {
		add (getCowFood(i), getCowDrink(i), 1, 1);
	}
	// Source to food
    for (int i=1; i<=F; i++) {
        add (0, getFood(i), 1, 1);
    }
	// Drink to sink
	for (int i=1; i<=D; i++) {
		add (getDrink(i), 1, 1, 1);
	}
}

int getFood(int a) {
    return a+1+N*2;
}

int getCowFood(int a) {
	return a+1;
}

int getDrink(int a) {
    return a+1+N*2+F;
}

int getCowDrink(int a) {
	return a+1+N;
}

void add (int u, int v, int ca, int co) {
    to[m] = v;
    next[m] = start[u];
    start[u] = m;
    cap[m] = ca;
    cost[m] = co;
    m++;

    // Add reverse edges too
    to[m] = u;
    next[m] = start[v];
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
	for (int e = start[u]; ~e; e = next[e]) {
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
