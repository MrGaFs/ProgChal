#include<stdlib.h>
#include<stdio.h>

int dialogues;
char lines[105][105];

int main() {
  // Read in
  scanf("%d\n", &dialogues);
  for (int i=0; i<dialogues; i++) {
    char current = getchar();
    while (current!= '!') {
      for (int j=0; j<100; j++) {
        if (current == '\n') {
          continue;
        }
        for (int k=0; k<100; k++) {
          lines[j][k] = current;
        }
      }
      current = getchar();
    }
  }
  return EXIT_SUCCESS;
}
