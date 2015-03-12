#include<stdlib.h>
#include<stdio.h>
#include<math.h>

int main() {
  int scenarios;
  scanf("%d", &scenarios);
  for(int x=0; x<scenarios; x++) {
    int n;
    scanf("%d\n", &n);
    // If 2+4*n, then only two children (+/- 1 (2^1-1))
    // If 4+8*n, then two layers below (+/- 3 (2^2-1))
    // If 8+16*n, three layers below (+/- 7 (2^3-1))
    // ? If 16+32*n, three layers below, (+/- 15 (2^4-1)) ? Check this, see if it works.
    // Largest power of 2 indicates level
    // If odd, then its a leaf, else  

    int modulo = 2;
    while (n%modulo == 0) {
      modulo = modulo*2;
    }

    int min = n - (modulo/2)+1;
    int max = n + (modulo/2)-1;

    printf("%d %d\n", min, max); 

  }
  return EXIT_SUCCESS;
}
