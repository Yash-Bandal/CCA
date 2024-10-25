#include <bits/stdc++.h>
using namespace std;

int n;
vector<vector<int>> graph;
int minCost = INT_MAX;

// Function to calculate the lower bound (cost estimate) for a partial tour
int calculateBound(const vector<int>& currPath, vector<bool>& visited) {
    int bound = 0;

    // Adding cost of edges from each visited city
    for (int i = 0; i < n; i++) {
        if (visited[i]) {
            int minEdge = INT_MAX;
            for (int j = 0; j < n; j++) {
                if (!visited[j] && graph[i][j]) {
                    minEdge = min(minEdge, graph[i][j]);
                }
            }
            if (minEdge != INT_MAX) {
                bound += minEdge;
            }
        }
    }
    return bound;
}

// Recursive Branch and Bound function
void branchAndBound(int currPos, int count, int cost, vector<int>& currPath, vector<bool>& visited) {
    // Prune paths with cost exceeding the minimum known cost
    if (cost >= minCost) return;

    // Check if all cities are visited
    if (count == n) {
        if (graph[currPos][0]) {  // There is a return path to the starting city
            cost += graph[currPos][0];
            if (cost < minCost) {
                minCost = cost;
            }
        }
        return;
    }

    // Calculate a lower bound (cost estimate) for pruning unpromising paths
    int bound = calculateBound(currPath, visited);
    if (cost + bound >= minCost) return;

    // Recur to explore further cities
    for (int i = 0; i < n; i++) {
        if (!visited[i] && graph[currPos][i]) {
            visited[i] = true;
            currPath.push_back(i);
            branchAndBound(i, count + 1, cost + graph[currPos][i], currPath, visited);
            visited[i] = false;
            currPath.pop_back();
        }
    }
}

// Function to solve TSP using Branch and Bound
void solveTSP() {
    vector<int> currPath;
    vector<bool> visited(n, false);

    visited[0] = true;  // Start from the first city
    currPath.push_back(0);  // Starting city
    branchAndBound(0, 1, 0, currPath, visited);

    cout << "Minimum Cost: " << minCost << endl;
}

int main() {
    n = 4;
    graph = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };

    solveTSP();

    return 0;
}
