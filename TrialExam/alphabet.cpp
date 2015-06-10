#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

int main() {
	int cases;
	scanf("%d\n", &cases);
	for (int c=0; c<cases; c++) {
		long long configs = 1;
		string st;
		getline(cin, st);

		// remove the start and end ???s
		unsigned int s;
		for (s=0; s<st.size(); s++) {
			if (st[s] != '?') {
				break;
			}
		}
		unsigned int e;
		for (e=st.size(); e>=0; e--) {
			if (st[e] != '?') {
				break;
			}
		}

		int questions = 0;
		for (unsigned int i=s; i<e; i++) {
			if (st[i] == '?') {
				questions ++;
			} else {
				if (questions > 0) {
					char after = st[i];
					char before;
					if (i-questions > 0) {
						before = st[i-questions-1]; // check this
					//	printf("%c\n", before);
					} else { // first, can only have one conf.
						questions = 0;
						continue;
					}
					if (after != before) {
						configs = (configs*(questions+1))%1000000007;
					}
				}
				questions = 0;
			}
		}
		printf("%lli\n", configs);
	}
	return 0;
}

// If beginning or end, automatically 1 perm.
// If start and end chars the same, also 1
// Else, length +1
// Multiply batches together and modulo
