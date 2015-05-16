#include <iostream>
#include <stdio.h>
#include <vector>
#include <map>
#include <stack>

using namespace std;

int apple[100005]; // 1 indicates an apple, 0 indicates none
std::map<int, vector<int> > branches;

int stored[100005][2]; 	// Where the precomputed data is stored.
						// [0] = value of the node, [1] = end location

int DFS (std::stack<int> toInvestigate, int startIndex);
int forks;

int main() {
	scanf("%d\n", &forks);

	typedef std::map<int, vector <int> >::iterator it;

	// Construct the tree from inputs
	for(int i=1; i<forks; i++) {
		int parent, child;
		scanf("%d %d\n", &parent, &child);
		it current = branches.find(parent);
		if (current == branches.end()) { // Not in the map
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

	// Precompute the relevant array
	std::stack<int> toInvestigate;
	int dontcare = DFS(toInvestigate, 0);
			for(int k=1; k<forks; k++) {
				printf("%d ", stored[k][0]);
			}
			putchar('\n');
			for(int k=1; k<forks; k++) {
				printf("%d ", stored[k][1]);
			}
			putchar('\n');
	putchar(dontcare);

	char character;
	int location;
	int changes;
	scanf("%d\n", &changes);
	for(int j=0; j<changes; j++) {
		scanf("%s %d\n", &character, &location);
		if (character == 'Q') { // Enquiry
			// If no children (not in map), then return its value
			// Otherwise, do a DFS
		} else {
			if (apple[location] == 0) { 
				apple[location] = 1;
			} else {
				apple[location] = 0;
			}
//			for(int k=1; k<forks; k++) {
//				printf("%d ", apple[k]);
//			}
		}
	} 

	return 0;
}

std::stack<int> toInvestigate;
int startIndex = 0;

// Search through the given subtree, returns the end index
int DFS (std::stack<int> toInvestigate, int startIndex) {
	int endIndex = 0;
	typedef std::map<int, vector <int> >::iterator i;
	if (!toInvestigate.empty()) {
		// Investigate top node
		int name = toInvestigate.top();
		toInvestigate.pop();
		stored[startIndex][0] = name; // Store the value of the node

		// Check if current node has children
		i current = branches.find(name);
		if (current != branches.end()) { // Add the children
			vector<int> cur = current->second;
			for (std::vector<int>::iterator iter = cur.begin(); iter != cur.end(); iter ++) {
				toInvestigate.push(*iter);
			}
			endIndex =  DFS (toInvestigate, startIndex+1);
		} else {
			startIndex = endIndex; // Start and end is the same
			return startIndex;
		}
	}
	stored[startIndex][1] = endIndex;
	return endIndex;// Will this cause breakage?
}
