#include <cstdlib>
#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <vector>

using namespace std;

struct info {
	int w;
	int h;
};

int D;
info dolls[20010];

bool sortTheThing(info a, info b);

int main () {
	int cases;
	scanf("%d", &cases);
	for (int c=0; c<cases; c++) {
		scanf("%d", &D);
		for (int i=0; i<D; i++) {
			scanf("%d %d", &dolls[i].w, &dolls[i].h);
		}

		sort(dolls, dolls+D, sortTheThing);

/*		for (int i=0; i< D; i++) {
			printf("%d:%d ", dolls[i].w, dolls[i].h);
		}
		printf("\n");
*/
		// Longest increasing subsequence sorry not sorry
		vector<info> v;
		v.push_back(dolls[D-1]); // Largest
		for (int i=D-2; i>=0; i--) {
			int hi = v.size()-1;
			int lo = 0;
			int mid;
			while (lo <= hi) {
				mid = (hi+lo)/2;
				if (v[mid].w == dolls[i].w || v[mid].h <= dolls[i].h) {
					lo = mid+1;
				} else {
					hi = mid-1;
				}
			}
			if (lo == (int) v.size()) {
				v.push_back(dolls[i]);
			} else {
				v[lo].h = dolls[i].h;
				v[lo].w = dolls[i].w;
			}
		}
		printf("%d\n", (int) v.size());
	}  
	return 0;
}


bool sortTheThing(info a, info b) {
	if (a.w == b.w) {
		return a.h>b.h;
	}
	return a.w<b.w;
}
