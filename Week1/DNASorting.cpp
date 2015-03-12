#include<stdlib.h>
#include<stdio.h>

char data[100][50];

int bubbleSort(int c, int n);
void printString(int c, int n);

int main() {
  int m,n;
  scanf("%d %d\n", &n, &m);
  for(int i=0; i<m; i++) {
    for(int j=0; j<n; j++) {
      data[i][j] = getchar();
    }
    getchar();
  }

  // Get the measure of disorder for each
  int swaps[m];
  for (int c=0; c<m; c++) {
    swaps[c] = bubbleSort(c,n);
  }

  // print the strings in the appropriate order
  int minimum = 999999999;
  for (int k=0; k<m; k++) { // Iterate through m times
    int location;
    for (int l=0; l<m; l++) {
      if (swaps[l] < minimum) {
        minimum = swaps[l];
        location = l;
      }
    }
    printString(location, n);
    swaps[location] = 999999999;
    minimum = 999999999;
  }

  return EXIT_SUCCESS;
}

// m = which row being sorted
int bubbleSort(int c, int n) {
  int swaps = 0;
  int sweepSwaps = 1;
  // Copy data across to a local variable
  char datas[n];
  for(int j=0; j<n; j++) {
    datas[j] = data[c][j];
  }

  while (sweepSwaps > 0) {
    sweepSwaps = 0;
    for (int i=0; i<n-1; i++) {
      if (datas[i] > datas[i+1]) {
        char temp = datas[i];
        datas[i] = datas[i+1];
        datas[i+1] = temp;
        swaps ++;
        sweepSwaps ++;
      }
    }
  }
  return swaps;
}

void printString(int c, int n) {
  for(int i=0; i<n; i++) {
    putchar(data[c][i]);
  }
  putchar('\n');
}
