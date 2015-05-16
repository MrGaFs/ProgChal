#include <iostream>
#include <stdio.h>
#include <vector>
#include <map>
#include <stack>

using namespace std;

int apple[100005]; // 1 indicates an apple, 0 indicates none
std::map<int, vector<int> > branches;


int BFS (int root);
int forks;

int main() {
  scanf("%d\n", &forks);

  typedef std::map<int, vector <int> >::iterator it;

  apple[forks] = 1; // Outside loop below

  for(int i=1; i<forks; i++) {
    apple[i] = 1; // Start with apple on each fork
    int parent, child;
    scanf("%d %d\n", &parent, &child);
    it current = branches.find(parent);
    if (current == branches.end()) { // Not in the map, TODO: Improve time complexity of this step; ?make it an array
      std::vector<int> toAdd;
      toAdd.push_back(child);
      branches.insert(std::pair<int, vector<int> >(parent, toAdd));
      it current = branches.find(parent);
      vector<int> cur = current->second;
    } else {
      current->second.push_back(child);
      vector<int> cur = current->second;
    }
  } 

  char character;
  int location;
  int changes;
  scanf("%d\n", &changes);
  for(int j=0; j<changes; j++) {
    scanf("%s %d\n", &character, &location);
    if (character == 'Q') { // Enquiry
      // If no children (not in map), then return its value
      // Otherwise, do a BFS
      if (branches.find(location) == branches.end()) {
        printf("%d\n", apple[location]);
      } else {
        printf("%d\n", BFS(location));
      }
    } else {
      if (apple[location] == 0) { // No apple there
        apple[location] = 1;
      } else {
        apple[location] = 0;
      }
//      for(int k=1; k<forks; k++) {
//        printf("%d ", apple[k]);
//      }
    }
  } 

  return 0;
}

// Search through the given subtree
int BFS (int root) {
  std::stack<int> toInvestigate;
  toInvestigate.push(root);

  int apples = 0;
  typedef std::map<int, vector <int> >::iterator i;

  while(!toInvestigate.empty()) {
    int name = toInvestigate.top();
    toInvestigate.pop();
    apples = apples + apple[name]; // Adds apples to the counter
//    printf("NAME: %d, APPLES: %d, ?Apple: %d\n", name, apples, apple[name]);

    i current = branches.find(name);
    if (current != branches.end()) { // In map, add the elements
      vector<int> cur = current->second;
      for (std::vector<int>::iterator iter = cur.begin(); iter != cur.end(); iter ++) {
        toInvestigate.push(*iter);
      }
    }
  }
  return apples;
}
