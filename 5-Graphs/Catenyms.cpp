#include <stdlib.h>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>

std::vector<int> adjacent[26]; // All my links are here in int form
std::stack<std::string> st;
std::string dict[1005]; // This is where my words live
bool visited[1005];
int parent[1005]; // Union find to make sure one graph
int startLetter[26]; // Check oddness to find if a Euler path exists
int endLetter[26]; // As above
int odds; // Odd powered vertices
int words;


void clearSlate (int words);
bool isEuler ();
bool isGraph ();
void Union (int a, int b);
int find (int a);
void dfs (int start);
void euler (int words);
void printCatenym();

int main () {
	int cases;
	scanf("%d", &cases);
	for (int c=0; c<cases; c++) {
		scanf("%d\n", &words);
		clearSlate(words);
		for (int w=0; w<words; w++) {
			std::getline(std::cin, dict[w]);
		}
		std::sort(dict, dict+words);
		for (int i=0; i<words; i++) {
			int start = dict[i][0]-'a';
			int end = dict[i][(dict[i].length())-1]-'a';
			adjacent[start].push_back(end);
			visited[start] = visited[end] = 1;
			startLetter[start] ++;
			endLetter[end] ++;
			Union(start, end);
		}

		if (isEuler() == false) {
			printf("***\n");
		} else if (isGraph() == false) {
            printf("***\n");
		} else {
			euler(words);
			printCatenym();
		} 

	}
	return 0;
}

// http://www.ctl.ua.edu/math103/euler/ifagraph.htm
// Find Eulerian Path/Circuit
// Path exists when the graph has 2 nodes of odd degree/ no odd degrees
// This as per told in class. :D
// DFS, adding an edge to a stack each time
// When you reach a node with no edges to go to, pop from stack
void euler(int words) {
	int start;
	if (odds > 0) {
		for (int i=0; i<26; i++) {
			if (startLetter[i]-endLetter[i] == 1) { // Odd vertex
				start = i;
				break;
			}
		}
	} else {
		for (int i=0; i<26; i++) {
			if (startLetter[i] > 0) {
				start = startLetter[i];
				break;
			}
		}
	}
	for (int i=0; i<=words; i++) {
		visited[i] = 0;
	}
	dfs(start);
}

void analysePath(int startChar, int endChar) {
	for (int i=words-1; i>=0; i--) {
        if (visited[i] == 0) {
            if (dict[i][0]-'a' == startChar) {
                if (dict[i][(dict[i].length())-1]-'a' == endChar) {
                    st.push(dict[i]);
                    visited[i] = 1;
                    break;
                }
            }
        }
    }
}

void dfs (int start) {
	while(!adjacent[start].empty()) {
		int tmp = *(adjacent[start].begin());
		adjacent[start].erase(adjacent[start].begin());
		dfs(tmp);
		analysePath(start, tmp);
	}
}

// Check if an Euler path/circuit is present
bool isEuler () {
	odds = 0;
	for(int i=0; i<26; i++) {
		if (abs(startLetter[i] - endLetter[i]) > 1) { // Dangly bits
			return false;
		}
		if (abs(startLetter[i] - endLetter[i]) == 1) { // Odd vertices
			odds ++;
		}
	}
	if (odds > 2) { // Too many odd vertices
		return false;
	}
	return true;
}

// Check if a single graph is present, or if theres a forest
bool isGraph() {
	int start;
	for (int i=0; i<26; i++) {
		if (visited[i] == 1) {
			start = find(i);
			break;
		}
	}

	for (int i=0; i<26; i++) {
		if (visited[i] == 1) {
			if (start != find(i)) { // Forest
				return false;
			}
		}
	}
	return true;
}

void Union(int a, int b) {
	a = find(a);
	b = find(b);
	if (a != b) {
		parent[b] = a;
	}
}

int find(int a) {
	if (a != parent[a]) {
		parent[a] = find(parent[a]);
	}
	return parent[a];
}

void clearSlate(int words) {
	for (int i=0; i<words; i++) {
		visited[i] = false;
		parent[i] = i;
	}
	while (!st.empty()) {
		st.pop();
	}
	odds = 0;
}

void printCatenym() {
	std::string tmp = st.top();
	std::cout << tmp;
	st.pop();
	while (!st.empty()) {
		tmp = st.top();
		std::cout << "." << tmp;
		st.pop();
	}
	printf("\n");
}
