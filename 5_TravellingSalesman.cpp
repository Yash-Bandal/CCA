#include <bits/stdc++.h>
using namespace std;

int tsp(int pos, int visited, const vector<vector<int>>& graph, int n,
vector<vector<int>>& dp, vector<vector<int>>& parent) {
    if (visited == (1 << n) - 1) {
        return graph[pos][0];
    }
    if (dp[pos][visited] != -1) {
        return dp[pos][visited];
    }
    int minCost = INT_MAX;
    for (int city = 0; city < n; city++) {
        if ((visited & (1 << city)) == 0) {
 int newCost = graph[pos][city] + tsp(city, visited | (1 << city), graph, n, dp, parent);
            if (newCost < minCost) {
                minCost = newCost;
                parent[pos][visited] = city;
            }
        }
    }
    return dp[pos][visited] = minCost;
}

void printPath(int n, vector<vector<int>>& parent) {
    int visited = 1;
    int pos = 0;
    cout << "Path: 0 ";
    while (true) {
        int nextCity = parent[pos][visited];
        if (nextCity == -1) break;
        cout << "-> " << nextCity;
        visited |= (1 << nextCity);
        pos = nextCity;
    }
    cout << "-> 0" << endl;
}

int main() {
    vector<vector<int>> graph = {
        {0, 29, 20, 21},
        {29, 0, 15, 17},
        {20, 15, 0, 28},
        {21, 17, 28, 0}
    };
    int n = graph.size();
    vector<vector<int>> dp(n, vector<int>(1 << n, -1));
    vector<vector<int>> parent(n, vector<int>(1 << n, -1));
    int minCost = tsp(0, 1, graph, n, dp, parent);
    cout << "Minimum Cost: " << minCost << endl;
    printPath(n, parent);
    return 0;
}
-------------------------
Output:
-Minimum Cost: 73
Path: 0 -> 2-> 1-> 3-> 0

