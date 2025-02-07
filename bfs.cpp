#include <iostream>
#include <queue>
#include <vector>

using namespace std;

void bfs(int start, const vector<vector<int> >& graph) {
    vector<bool> visited(graph.size(), false);
    queue<int> q;
    
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int current = q.front();
        q.pop();
        cout << current << " ";

        // Change range-based for loop to a traditional for loop
        for (size_t i = 0; i < graph[current].size(); ++i) {
            int neighbor = graph[current][i];
            if (!visited[neighbor]) {
                q.push(neighbor);
                visited[neighbor] = true;
            }
        }
    }
}

int main() {
    int nodes = 6;
    vector<vector<int> > graph(nodes);

    // Use push_back() to add neighbors instead of initialization lists
    graph[0].push_back(1);
    graph[0].push_back(2);
    graph[1].push_back(0);
    graph[1].push_back(3);
    graph[1].push_back(4);
    graph[2].push_back(0);
    graph[2].push_back(4);
    graph[3].push_back(1);
    graph[3].push_back(5);
    graph[4].push_back(1);
    graph[4].push_back(2);
    graph[4].push_back(5);
    graph[5].push_back(3);
    graph[5].push_back(4);

    int startNode = 0;
    bfs(startNode, graph);

    return 0;
}

