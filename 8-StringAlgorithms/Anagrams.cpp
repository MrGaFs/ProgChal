#include <cstdlib>
#include <stdio.h>
#include <string>
#include <map>
#include <utility>
#include <iostream>
#include <algorithm>
#include <set>
#include <queue>
#include <functional>

typedef std::pair<int, std::set<std::string> > Pair; 
#define String std::string

void solve ();
bool compare(Pair a, Pair b);

std::map<String, Pair> words;

int main() {
	String tmp;
	int largest_group = 1;
	while(getline (std::cin, tmp)) {
		// get map key via sorting
		String sorted;
		sorted = tmp;
		std::sort(sorted.begin(), sorted.end());
		// add to map
		std::map<String, Pair>::iterator it;
		it = words.find(sorted);
		if (it != words.end()) { // already exists
			(it->second).first ++;
			((it->second).second).insert(tmp);
			if (largest_group < (it->second).first) {
				largest_group = (it->second).first;
			}
		} else {
			std::set<String> vec;
			vec.insert(tmp);
			words[sorted]=Pair(1, vec);
		}
	}

/*	map<string, pair<int, vector<string> > >::iterator it;
	for (it=words.begin(); it != words.end(); ++it) {
		cout << it->first << " => " << (it->second).first << " : ";
		vector<string> vect = (it->second).second;
		for (unsigned int i=0; i < vect.size(); i++) {
			cout << vect[i] << ", ";
		}
		cout << '\n';
	} */

	// Print the largest five

	solve();

	return 0;
}

struct cmp {
	bool operator() (Pair a, Pair b) {
		if (a.first == b.first) {
			return (a.second > b.second);
		} else {
			return a.first<b.first;
		}
	} 
};

void solve () {
	// insert to a priority queue
	std::priority_queue<Pair, std::vector<Pair>, cmp> pq;
	std::map<String, Pair>::iterator it;
	for (it = words.begin(); it != words.end(); ++it) {
		pq.push(it->second);
	}

	int printedLines = 0;
	while (!pq.empty() && printedLines < 5) {
		std::cout << "Group of size " << (pq.top()).first << ": ";
		// print each element in the map
		std::set<std::string> wordSet = (pq.top()).second;
		for (std::set<std::string>::iterator it = wordSet.begin(); it != wordSet.end(); it++) {
			std::cout << *it << " ";
		}
		std::cout << ".\n";
		pq.pop();
		printedLines ++;
	}
}


