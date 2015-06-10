#include<stdlib.h>
#include<stdio.h>
#include<math.h>

int findFactor(int n, int factor);

int main() {
  int scenarios;
  scanf("%d", &scenarios);
  for(int x=0; x<scenarios; x++) {
    int n;
    scanf("%d\n", &n);
    // Find closest multiple of 5 below the number, then divide that by 5
    // Then find the multiples of 25, and add them too (as they have 2 5s)
    // So on and so forth for all powers of 5
    // http://www.purplemath.com/modules/factzero.htm
    int zeroes = 0;
    if (n == 0) {
      zeroes = 1;
    } else if (n >= 5) { // < 5 has no zeroes
      int factor = 5;
      int toAdd = 1;
      while (toAdd > 0) {
        toAdd = findFactor(n, factor);
        zeroes = zeroes + toAdd;
        factor = factor*5;
      }
    }

    printf("%d\n", zeroes);
  }
  return EXIT_SUCCESS;
}

int findFactor(int n, int factor) {
  return (n-n%factor)/factor;
}
