#include <cstdio>
#include <cstdlib>
#include <vector>

int subtree[20005];
std::vector<int> edges[20005];
int nodes;
int balanceNode;
int balanceSize;

int findBal(int node, int curr);
void solve(int size, int parent, int curr);
 
int main() {
    int cases;
    scanf("%d", &cases);
    for (int i = 0; i < cases; i++) {
        scanf("%d", &nodes);
        for (int i = 0; i < nodes+1; i++) {
            edges[i].clear();
            subtree[i] = 0;
        }

        for (int j=1; j<nodes; j++) {
            int a, b;
            scanf("%d %d", &a, &b);
            edges[a].push_back(b);
            edges[b].push_back(a);
        }

        //Find a leaf
        int leaf = -1;
        for (int j=1; j<=nodes; j++) {
            if (edges[j].size() == 1) {
                leaf = j;
                break;
            }
        }

        balanceNode = leaf;
        balanceSize = nodes-1;

        findBal(0, leaf);
        solve(0, 0, leaf);

        printf("%d %d\n", balanceNode, balanceSize);

/*		for (int i=1; i<=nodes; i++) {
            printf("%d ", subtree[i]);
        }
		putchar('\n');

*/
/*		for (int i=1; i<=cong; i++) {
			printf("%d: ", i);
			for (std::vector<int>::const_iterator it = edges[i].begin(); it != edges[i].end(); ++it) {
				std::cout << *it << ' ';
			}
			std::cout << '\n';
		}
*/
	}
	return 0;
}

void solve(int pSize, int parent, int curr) {
    int myBalance = pSize;
    for (unsigned int i=0; i<edges[curr].size(); i++) {
        if (edges[curr][i] != parent) {
            int cSize = subtree[edges[curr][i]];
            if (cSize > myBalance) myBalance = cSize;
        }
    }

    if (myBalance < balanceSize) {
        balanceSize = myBalance;
        balanceNode = curr;
    }
	if (myBalance == balanceSize && curr < balanceNode) {
        balanceSize = myBalance;
        balanceNode = curr;
	}

    for (unsigned int i=0; i<edges[curr].size(); i++) {
        int child = edges[curr][i];
        if (child != parent) {
            solve(nodes-subtree[child], curr, child);
        }
    }
}

int findBal(int parent, int curr) { 
    if (edges[curr].size() == 1 && edges[curr][0] == parent) {
        subtree[curr] = 1;
        return 1;
    }

    int size = 1;
    for (unsigned int i = 0; i < edges[curr].size(); i++) {
        if (edges[curr][i] != parent) {
            size = size + findBal(curr, edges[curr][i]);
        }
    }

    subtree[curr] = size;
    return size;
}
