#include <iostream>
#include <string>
#include <map>
#include <stdio.h>

using namespace std;

int main() {
  int total = 0;
  std::map<string, int> trees;
  std::string name;
  typedef std::map<string, int>::iterator it;

  while (std::getline(std::cin, name)) {
    it current = trees.find(name);
    if (current == trees.end()) { // Not in the map
      trees.insert(std::pair<string,int>(name, 1));
      total ++;
    } else {
      current->second = current->second + 1;
      total ++;
    }
  }

  typedef std::map<string, int>::iterator i;
  for (i iterator = trees.begin(); iterator != trees.end(); iterator ++) {
    printf("%s %0.4f\n", iterator->first.c_str(), float(iterator->second)/total*100);
  }
  return 0;
}
