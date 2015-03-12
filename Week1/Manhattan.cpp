#include<stdlib.h>
#include<stdio.h>

int distanceFromCentre(int i, int u);

int main() {
  int scenarios;
  scanf("%d", &scenarios);
  int scenList[scenarios];
  for(int x=0; x<scenarios; x++) {
    int dis;
    scanf("%d", &dis);
    scenList[x] = dis;
  }

  for(int a=0; a<scenarios; a++) {
    int distance = scenList[a];
    printf("Scenario #%d:\n", a+1);
    int edgeLength = 2*distance+1;
    for (int k=0; k<edgeLength; k++) {
      printf("slice #%d:\n", k+1);
      for (int i=0; i<edgeLength; i++) {
        for (int j=0; j<edgeLength; j++) {
          int dist = distanceFromCentre(i, distance) +
                     distanceFromCentre(j, distance) +
                     distanceFromCentre(k, distance);
         if (dist > distance) {
           printf(".");
         } else {
           printf("%d", dist);
         } 
        }
        printf("\n");
      }
    }
    printf("\n");
  }

  return EXIT_SUCCESS;
}

int distanceFromCentre(int i, int u) {
  return abs(i-u);
}
