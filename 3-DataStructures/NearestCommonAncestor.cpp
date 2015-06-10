#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

int edges[10005]; // Value is the parent.

void findPath (int child, vector<int> &path);

int main() {
  int tests ;
  scanf("%d\n", &tests);
  // Iterate through each test
  for (int i=0; i<tests; i++) {
    int nodes;
    scanf("%d\n", &nodes);
    for (int k=0; k<nodes+1; k++) {
      edges[k+1] = 0;
    }
    for (int j=1; j<nodes; j++) {
      int parent, child;
      scanf("%d %d\n", &parent, &child);
      // Construct the tree
      edges[child] = parent;
    }

    // Now find the common ancestor
    int a, b;
    scanf("%d %d\n", &a, &b);

    if (nodes == 2) {
      if (edges[a] == 0) {
        printf("%d\n", a);
      } else {
        printf("%d\n", b);
      }
    } else {
      if (edges[a] == b) {
        printf("%d\n", b);
      } else if (edges[b] == a) {
        printf("%d\n", a);
      } else {
        vector<int> pathA, pathB;
        findPath(a, pathA);
        findPath(b, pathB);

        // Deal with small elements
        if (pathA.size() < 2) {
          printf("%d\n", a);
        } else if (pathB.size() < 2) {
          printf("%d\n", b);
        } else {
          std::vector<int>::reverse_iterator rib = pathB.rbegin();
          std::vector<int>::reverse_iterator temp;
          for (std::vector<int>::reverse_iterator ria = pathA.rbegin(); ria != pathA.rend(); ria ++) {
            if (*ria != *rib) {
              printf("%d\n", *temp);
              break;
            } else {
              rib ++;
              temp = ria;
            }
          }
        }
      } 
    }
  }
  return 0;
}

void findPath (int child, vector<int> &path) {
  int current = child;
  path.push_back(current);
  while (current != 0) {
    path.push_back(current);
    current = edges[current];
//    printf("%d ", current);
  }
//  printf("\n");
}
