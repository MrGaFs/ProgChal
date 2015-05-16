#include<stdlib.h>
#include<stdio.h>

char cows[105][105];

int test(int x, int y, int n);
int isJ(int x, int y);

int main() {
  int n;
  scanf("%d\n", &n);
  for(int i=0; i<n; i++) {
    for(int j=0; j<n; j++) {
      cows[i][j] = getchar();
    }
    getchar();
  }

  int longest = 0;
  for (int y1 = 0; y1 < n; y1++) {
    for (int x1 = 0; x1 < n; x1++) {
      if (cows[y1][x1] == 'B') {
        continue;
      }
      for (int y2 = y1; y2 < n; y2++) {
        for (int x2 = x1+1; x2 < n; x2++) {
          if (cows[y2][x2] == 'B') {
            continue;
          }
          // Get the differences in x and y testues
          int xc = x2 - x1;
          int yc = y2 - y1;
          // Calculate the other vertices
          int x3 = x1 - yc;
          int y3 = y1 + xc;
          int x4 = x2 - yc;
          int y4 = y2 + xc;
          if (test(x3, y3, n) != -1 && test(x4, y4, n) != -1) {
            if (isJ(x1,y1) + isJ(x2,y2) + isJ(x3,y3) + isJ(x4,y4) > 2) {
              //printf("x1:%d y1:%d x2:%d y2:%d x3:%d y3:%d x4:%d y4:%d\n", x1,y1,x2,y2,x3,y3,x4,y4);
              int size = xc*xc+yc*yc; //Doing it this way removes negatives
              if (size > longest) {
                longest = size;
              }
            }
          }
        }
      }
    }
  }

  printf("%d\n", longest);
  return EXIT_SUCCESS;
}

int isJ(int x, int y) {
  if (cows[y][x] == 'J') {
    return 1;
  }
  return 0;
}

int test(int x, int y, int n) {
  if (x < 0 || x >= n) {
    return -1;
  } else if (y < 0 || y >= n) {
    return -1;
  } else if (cows[y][x] == 'B') {
    return -1;
  } else {
    return 0;
  }
}
