#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// Function to implement the Min-Max algorithm
int minimax(int depth, int nodeIndex, bool isMax, vector<int>& scores, int h) {
    // Base case: if leaf node is reached
    if (depth == h) {
        return scores[nodeIndex];
    }

    if (isMax) {
        // Maximizer's turn
        return max(minimax(depth + 1, nodeIndex * 2, false, scores, h),
                   minimax(depth + 1, nodeIndex * 2 + 1, false, scores, h));
    } else {
        // Minimizer's turn
        return min(minimax(depth + 1, nodeIndex * 2, true, scores, h),
                   minimax(depth + 1, nodeIndex * 2 + 1, true, scores, h));
    }
}

int main() {
    int numLeafNodes;

    // Prompt user for number of leaf nodes
    cout << "Enter the number of leaf nodes: ";
    cin >> numLeafNodes;

    // Ensure the number of leaf nodes is a power of two
    if ((numLeafNodes & (numLeafNodes - 1)) != 0) {
        cout << "Number of leaf nodes must be a power of 2." << endl;
        return -1;
    }

    vector<int> scores(numLeafNodes);

    // Input leaf node scores from user
    cout << "Enter the scores for each leaf node:" << endl;
    for (int i = 0; i < numLeafNodes; ++i) {
        cout << "Score for leaf node " << i + 1 << ": ";
        cin >> scores[i];
    }

    int treeDepth = log2(numLeafNodes); // Calculate height of the tree

    cout << "The optimal value is: " << minimax(0, 0, true, scores, treeDepth) << endl;
    
    return 0;
}

