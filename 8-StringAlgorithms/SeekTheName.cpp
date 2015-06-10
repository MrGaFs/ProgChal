#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <string.h>

using namespace std;

const int MAX = 500005;

void init();
int kmp(string s);

int pre[MAX]; 
int ans[MAX];

int main() {
	string parentName;
	while(getline(cin, parentName)) {
		init();
		int c = kmp(parentName);
//		for (unsigned int i=0; i<parentName.size(); i++) {
//			printf("%d ", ans[i]);
//		}
//		putchar('\n');

		for (int i=c-1; i>=0; i--) {
			printf("%d ", ans[i]);
		}
		int s = parentName.size();
		printf("%d\n", s);
	}
	return 0;
}

void init() {
	memset(pre, 0, sizeof(pre));
    memset(ans, 0, sizeof(ans));
    pre[0] = -1;
}

// Code from lectures
// then totally rewritten, awks
int kmp(string s) {
	int len = s.size();
	int i = 0;
	int j = -1; // starting at the no-parent route
				// just like batman
	while (i<len) {
		if (j==-1 || s[i]==s[j]) {
			i++;
			j++;
			pre[i] = j;
		} else {
			j = pre[j];
		}
	}
	int cnt = 0;
	int t = pre[len-1];
	while (t != -1) {
//		printf("%d\n", t);
		if (s[t] == s[len-1]) {
			ans[cnt++] = t+1;
		}
		t = pre[t];
	}
	return cnt;
}
