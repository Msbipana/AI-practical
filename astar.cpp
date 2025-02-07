#include <iostream>
#include <queue>
#include <cmath>
#include <vector>

using namespace std;

// Custom Pair structure to replace std::pair in C++98
struct Pair {
    int first, second;
    Pair(int x = 0, int y = 0) : first(x), second(y) {}
};

// Node structure definition
struct Node {
    int x, y;
    double cost, heuristic;
    Node* parent;

    // Node constructor
    Node(int x_val, int y_val, double cost_val, double heuristic_val, Node* parent_val)
        : x(x_val), y(y_val), cost(cost_val), heuristic(heuristic_val), parent(parent_val) {}

    double totalCost() const {
        return cost + heuristic;  // Sum of cost and heuristic
    }
};

// Comparison functor for Node, to use with priority_queue
struct CompareNode {
    bool operator()(const Node& a, const Node& b) const {
        return a.totalCost() > b.totalCost();  // Compare based on total cost
    }
};

// Euclidean distance function
double euclideanDistance(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

// Check if a position is valid
bool isValid(int x, int y, int rows, int cols, const vector<vector<int> > & grid) {
    return (x >= 0 && x < rows && y >= 0 && y < cols && grid[x][y] == 0);
}

// Print the path from start to goal
void printPath(Node* node) {
    if (node == NULL) return;
    printPath(node->parent);
    cout << "(" << node->x << ", " << node->y << ") ";
}

// A* Search algorithm implementation
void aStarSearch(const vector<vector<int> > & grid, Pair start, Pair goal) {
    int rows = grid.size();
    int cols = grid[0].size();

    // Print initial and goal states
    cout << "Initial State: (" << start.first << ", " << start.second << ")" << endl;
    cout << "Goal State: (" << goal.first << ", " << goal.second << ")" << endl;

    // Priority Queue using CompareNode
priority_queue<Node, vector<Node> , CompareNode> openList;

    vector<vector<bool> >closedList(rows, vector<bool>(cols, false));

    // Start node setup
    Node* startNode = new Node(start.first, start.second, 0, euclideanDistance(start.first, start.second, goal.first, goal.second), NULL);
    openList.push(*startNode);

    // Movement directions
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    while (!openList.empty()) {
        Node current = openList.top();
        openList.pop();

        if (closedList[current.x][current.y]) continue;
        closedList[current.x][current.y] = true;

        if (current.x == goal.first && current.y == goal.second) {
            cout << "Path found: ";
            printPath(&current);
            cout << endl;
            return;
        }

        for (int i = 0; i < 4; i++) {
            int newX = current.x + dx[i];
            int newY = current.y + dy[i];

            if (isValid(newX, newY, rows, cols, grid) && !closedList[newX][newY]) {
                double newCost = current.cost + 1; // Assuming uniform cost for each move
                double heuristic = euclideanDistance(newX, newY, goal.first, goal.second);
                Node* neighbor = new Node(newX, newY, newCost, heuristic, new Node(current));

                openList.push(*neighbor);
            }
        }
    }

    cout << "No path found." << endl;
}

int main() {
    // Define grid (0 = open space, 1 = blocked)
    vector<vector<int> > grid(5, vector<int>(5, 0));

    // Manually assign values to the grid
    grid[0][0] = 0; grid[0][1] = 0; grid[0][2] = 0; grid[0][3] = 0; grid[0][4] = 1;
    grid[1][0] = 0; grid[1][1] = 1; grid[1][2] = 0; grid[1][3] = 0; grid[1][4] = 1;
    grid[2][0] = 0; grid[2][1] = 1; grid[2][2] = 0; grid[2][3] = 1; grid[2][4] = 0;
    grid[3][0] = 0; grid[3][1] = 0; grid[3][2] = 0; grid[3][3] = 1; grid[3][4] = 0;
    grid[4][0] = 1; grid[4][1] = 1; grid[4][2] = 0; grid[4][3] = 0; grid[4][4] = 0;

    Pair start(0, 0);  // Start position
    Pair goal(4, 4);   // Goal position

    aStarSearch(grid, start, goal);

    return 0;
}

