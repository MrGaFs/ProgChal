#include<stdlib.h>
#include<stdio.h>
#include<math.h>

int isBinary(int n);
long long search(unsigned long long current, int step);
int n=1;
unsigned long long answer;

int main() {
  scanf("%d\n", &n);
  while(n != 0) {
   //http://math.stackexchange.com/questions/388165/how-to-find-the-smallest-n-with-just-0-and-1-which-is-divided-by-a-give 
    if (isBinary(n) == 1) {
      printf("%d\n", n);
    } else {
      search(1, 0);
      printf("%llu\n", answer);
    }
    scanf("%d\n", &n);
  }

  return EXIT_SUCCESS;
}

long long search(unsigned long long current, int step) {
  if (step == 20) {
    return 0;
  } else if (current%n == 0) { // Found a multiplt
    answer = current;
    return 1;
  } else {
    if (search(current*10, step+1)) {
      return 1;
    }
    if (search(current*10+1, step+1)) {
      return 1;
    }
  }
  return 0;
}

int isBinary(int n) {
  int temp;
  while(n != 0) {
    temp = n%10;
    if (temp > 1) {
      return 0;
    } else {
        n = n/10;
    }
  }
  return 1;
}
