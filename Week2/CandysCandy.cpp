#include<stdlib.h>
#include<stdio.h>
#include<math.h>

int flavours[100000];

int main() {
  int varieties = 1;
  while (scanf("%d", varieties) != 0) {
	for (int i=0; i<varieties; i++) {
    	scanf("%d", flavours[i]);
		getchar();
	}

    // Plz be putting at the end.
    scanf("%d", varieties);
  }

  return EXIT_SUCCESS;
}
