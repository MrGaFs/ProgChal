#include <cstdlib>
#include <stdio.h>



int main() {
	int cases;
	scanf("%d\n", &cases);
	for (int c=0; c<cases; c++) {
		int unknown=0;
		int x = 0;
		int y = 0;
		char curr;
		scanf("%c", &curr);
		while(curr != '\n') {
			if (curr == 'R') {
				x ++;
			} else if (curr == 'L') {
				x --;
			} else if (curr == 'U') {
				y ++;
			} else if (curr == 'D') {
				y --;
			} else if (curr == '?') {
				unknown ++;
			}
	        scanf("%c", &curr);
		}
		printf("%d %d %d %d\n", x-unknown, y-unknown, x+unknown, y+unknown);
	}
	return 0;
}
