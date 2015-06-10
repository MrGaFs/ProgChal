#include <cstdlib>
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

bool isSubSeq(string &subs, string &mains, unsigned int m, unsigned int n);

int main() {
	string subseq, mainseq;
	while(cin >> subseq) {
		cin >> mainseq;
//		cout << subseq << ' ' << mainseq << '\n';
		bool subPresent = isSubSeq(subseq, mainseq, subseq.size(), mainseq.size());
		if (subPresent == true) {
			printf("Yes\n");
		} else {
			printf("No\n");
		}
	}
	return 0;
}

bool isSubSeq(string &subs, string &mains, unsigned int m, unsigned int n) {
	if (m == 0) {
		return true;
	}
	if (n == 0) {
		return false;
	}

	if (subs[m-1] == mains[n-1]) { // match
		return isSubSeq(subs, mains, m-1, n-1);
	}

	return isSubSeq(subs, mains, m, n-1);
}
