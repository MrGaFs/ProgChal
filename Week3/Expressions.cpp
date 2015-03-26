#include <iostream>
#include <stack>
#include <queue>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

typedef struct node *link;

struct node {
	link right;
	link left;
	char value;
};

void printTree(link n);
void freeNode(link n);
link newNode(char value);
void freeNode(link n);

// http://www.dreamincode.net/forums/topic/37428-converting-and-evaluating-infix-postfix-and-prefix-expressions-in-c/

std::stack<char> toPrint;

int main() {
	int inputs;
	scanf("%d\n", &inputs);
	for (int i=0; i<inputs; i++) {
		std::stack<link> st;

		char c = getchar();
		// Put nodes onto a stack
		while (c != '\n') {
			if (islower(c)) { // A number
				link newN = newNode(c);
				st.push(newN);
			} else { // An operator
				link newN = newNode(c);
				newN->right = st.top();
				st.pop();
				newN->left = st.top();
 				st.pop();
				st.push(newN);
			}
			c = getchar();
		}
		link start = st.top(); // This is the root node containing everything
		printTree(start); 
		while (!toPrint.empty()) {
			putchar(toPrint.top());
			toPrint.pop();
		}
		putchar('\n');
	}
	return 0;
}

link newNode(char value) {
	link newN = (link)malloc(sizeof(link));
	newN->right = NULL;
    newN->left = NULL;
	newN->value = value;
	return newN;
}

void freeNode(link n) {
	free(n);
}


void printTree (link n) {
	std::string toReturn;
	std::queue<link> currentLevel, nextLevel;
	currentLevel.push(n);
	while (!currentLevel.empty()) {
		link currNode = currentLevel.front();
		currentLevel.pop();
		if (currNode) {
			toPrint.push(currNode->value);
			nextLevel.push(currNode->left);
			nextLevel.push(currNode->right);
			freeNode(currNode);
		}
		if (currentLevel.empty()) {
			std::swap(currentLevel, nextLevel);
		}
	}

}
