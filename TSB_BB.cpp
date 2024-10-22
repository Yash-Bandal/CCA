#include <bits/stdc++.h>
using namespace std;

class TSP {
    int n;
    vector<vector<int>> graph;
    vector<bool> visited;
    int minCost = INT_MAX;
    vector<int> bestPath;

public:
    TSP(int n, const vector<vector<int>>& graph) : n(n), graph(graph), visited(n, false) {}

    void tsp(int currPos, int count, int cost, vector<int>& path) {
        if (count == n && graph[currPos][0]) { // All cities visited
            cost += graph[currPos][0]; // Return to starting city
            if (cost < minCost) {
                minCost = cost;
                bestPath = path;
                bestPath.push_back(0); // Adding the starting city to complete the tour
            }
            return;
        }

        for (int i = 0; i < n; i++) {
            if (!visited[i] && graph[currPos][i]) {
                visited[i] = true; // Mark city as visited
                path.push_back(i); // Add city to current path
                tsp(i, count + 1, cost + graph[currPos][i], path);
                visited[i] = false; // Backtrack
                path.pop_back(); // Remove city from current path
            }
        }
    }

    void solve() {
        visited[0] = true; // Start from the first city
        vector<int> path;
        path.push_back(0); // Starting city
        tsp(0, 1, 0, path);

        cout << "Minimum Cost: " << minCost << endl;
        cout << "Path: ";
        for (int city : bestPath) {
            cout << city << " ";
        }
        cout << endl;
    }
};

int main() {
    int n = 4;
    vector<vector<int>> graph = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };

    TSP tsp(n, graph);
    tsp.solve();

    return 0;
}
