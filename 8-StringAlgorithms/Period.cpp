#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <string.h>

using namespace std;

const int MAX = 1000005;

int par[MAX];

void kmp(string s);

int main () {
	int cases = 1;
	int n;
	scanf("%d\n", &n);
	while (n != 0) {
		memset(par, 0, sizeof(par));
		string str;
		getline(cin, str);
		kmp(str);
//		for (int i=0; i<n; i++) {
//			printf("%d ", par[i]);
//		}
//		putchar('\n');

		printf("Test case #%d\n", cases);
		for (int i=2; i<=n; i++) {
			// cant be size 0, must be a magic repeat
			if (par[i] != 0 && i%(i-par[i]) == 0) {
				printf("%d %d\n", i, i/(i-par[i])); //plz no modulo twice, youve already calculated that
			}
		}
		putchar('\n');

		scanf("%d\n", &n);
		cases ++;
	}
	return 0;
}

// Now with less kmp, more finding prefixes
void kmp(string s) {
	int n = s.size();
	int i=0, j=-1;
	par[0] = -1; // no parents for yooou
	while (i<n) {
		if (j==-1 || s[i] == s[j]) {
			i++;
			j++;
			par[i] = j;
		} else {
			j = par[j];
		}
	}
}
