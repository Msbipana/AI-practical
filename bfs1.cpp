#include <iostream>
#include <vector>
#include <queue>
using namespace std;
// Function to perform BFS on the graph
void BFS(int startNode, vector<vector<int>>& adjList, vector<bool>& visited) {
queue<int> q;
q.push(startNode);
visited[startNode] = true;
while (!q.empty()) {
int currentNode = q.front();
q.pop();
cout << currentNode << " "; // Output the current node
// Traverse the adjacent nodes
for (int neighbor : adjList[currentNode]) {
if (!visited[neighbor]) {
visited[neighbor] = true;
q.push(neighbor);
}
}
}
}
int main() {
int numNodes, numEdges;
cout << "Enter the number of nodes and edges: ";
cin >> numNodes >> numEdges;
vector<vector<int>> adjList(numNodes); // Adjacency list to represent the graph
vector<bool> visited(numNodes, false); // Visited array to keep track of visited nodes
coutfor (int i = 0; i < numEdges; ++i) {
int u, v;
cin >> u >> v;
adjList[u].push_back(v);
adjList[v].push_back(u); // For undirected graph, add both ways
}
int startNode;
cout << "Enter the starting node for BFS: ";
cin >> startNode;
cout << "BFS traversal starting from node " << startNode << ": ";
BFS(startNode, adjList, visited);
return 0;
}
