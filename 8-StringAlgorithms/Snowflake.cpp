#include <cstdlib>
#include <stdio.h>
#include <algorithm>

const int MAX = 100005;
const int B = 31;

int k = 6;
int n;
long long s[MAX][10];
long long H[MAX];

long long hash(int i);
bool findDuplicates();

int main() {
	scanf("%d", &n);
	for (int i=0; i<n; i++) {
		scanf("%lld %lld %lld %lld %lld %lld", &s[i][0], &s[i][1], 
				&s[i][2], &s[i][3], &s[i][4], &s[i][5]);
		std::sort(s[i], s[i]+6);
//		printf("%lld %lld %lld %lld %lld %lld\n", s[i][0], s[i][1],
//                s[i][2], s[i][3], s[i][4], s[i][5]);
		// Such hash
		H[i] = hash(i);
	}

	// Find duplicates
	std::sort(H, H+n);
	bool dupl = findDuplicates();
	if (dupl == true) {
		printf("Twin snowflakes found.\n");
	} else {
		printf("No two snowflakes are alike.\n");
	}
	return 0;
}

long long hash (int i) {
	return (s[i][0]+B*(s[i][1]+B*(s[i][2]+B*(s[i][3]+B*(s[i][4]+B*s[i][5])))));
}

bool findDuplicates() {
	for (int i=0; i<n-1; i++) {
		if (H[i] == H[i+1]) {
			return true;
		}
	}
	return false;
}
