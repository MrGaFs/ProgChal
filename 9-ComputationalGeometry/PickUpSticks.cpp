#include <cstdlib>
#include <stdio.h>
#include <utility>
#include <set>
#include <vector>
#include <math.h>

using namespace std;

const double EPS = 1e-8;
typedef pair<double, double> pt;
typedef pair<pt, pt> seg;
typedef pair<seg, int> stick;
#define x first
#define y second
pt operator-(pt a, pt b) {
 return pt(a.x - b.x, a.y - b.y);
} 

double cross(pt a, pt b);
bool ccw(pt a, pt b, pt c);
bool zero(double x);
bool overlap(seg a, seg b);
bool between(double a, double b, double x);
bool intersect(seg a, seg b);

int main () {
	int s;
	scanf("%d", &s);
	while (s != 0) {
		set<stick> sticks;
		for (int i=1; i<=s; i++) {
			// make data point
			pt one;
			scanf("%lf %lf", &one.x, &one.y);
			pt two;
			scanf("%lf %lf", &two.x, &two.y);
			seg st;
			st.x = one;
			st.y = two;
			stick curr;
			curr.x = st;
			curr.y = i;
			// check if on top (and remove overlapped sticks)
			vector<stick> toRemove;
			set<stick>::iterator it;
			for (it=sticks.begin(); it !=sticks.end(); ++it) {
				if (intersect(st, it->x) == true) { // overlap
					toRemove.push_back(*it);
				}
			}
			for (unsigned int j=0; j<toRemove.size(); j++) {
				sticks.erase(toRemove[j]);
			}
			sticks.insert(curr);
		}
		// Sticks remaining in the vector are all on top. Print them
		printf("Top sticks: ");
		set<int> remainder;
		set<stick>::iterator it = sticks.begin();
		while (it != sticks.end()) {
            remainder.insert(it->y);
			it++;
		}
		set<int>::iterator iter = remainder.begin();
		printf("%d", *iter);
		iter ++;
		while(iter != remainder.end()) {
			printf(", %d", *iter);
			iter ++;
		}
		printf(".\n");
		scanf("%d", &s);
	}
	return 0;
}


bool overlap(seg a, seg b) {
	return zero(cross(a.y - a.x, b.x - a.x)) && zero(cross(a.y - a.x, b.y - a.x));
}

double cross(pt a, pt b) {
	return a.x*b.y - a.y*b.x;
}

bool ccw(pt a, pt b, pt c) {
 return cross(b - a, c - a) >= 0;
}

bool zero(double x) {
	return fabs(x) <= EPS;
}

bool between(double a, double b, double x) {
	return min(a, b) <= x && x <= max(a, b);
}

bool intersect(seg a, seg b) {
	if (overlap(a, b)) {
		return between(a.x.x, a.y.x, b.x.x) || between(a.x.x, a.y.x, b.y.x)
		|| between(b.x.x, b.y.x, a.x.x) || between(b.x.x, b.y.x, a.y.x);
	}
	return ccw(a.x, a.y, b.x) != ccw(a.x, a.y, b.y)
	&& ccw(b.x, b.y, a.x) != ccw(b.x, b.y, a.y);
}
