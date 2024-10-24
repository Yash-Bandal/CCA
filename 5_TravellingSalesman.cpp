
#include <bits/stdc++.h>
using namespace std;
int n = 4;
int dp[16][4];
int dist[10][10] = {
    {0, 20, 42, 25},
    {20, 0, 30, 34},
    {42, 30, 0, 10},
    {25, 34, 10, 0}
    };
int VisitedAll = (1 << n) - 1; 
/*
 visited all is 1111 for 4 cities..given by binary
 For n = 4, 1 << 4 equals 16 in binary (10000).
 and 10000 - 1 = 1111

 Subtracting 1 gives 1111 (binary), which equals 15 in decimal.
 This 1111 means that all 4 cities have been visited (all bits are set to 1).

 mask =rep visited ..eg  0110 means cities 1 and 2 have been visited (since bits 1 and 2 are set to 1).
 pos = current city
*/
int tsp(int mask, int pos)
{
    if (mask == VisitedAll)   //ie 1111 == 1111..true
    { 
        //        curr city -> 0
        return dist[pos][0];  //return the distance from the current city back to the starting city (dist[pos][0]).
    }
    if (dp[mask][pos] != -1)
    {        //min dist
        return dp[mask][pos];  //f we already calculated the minimum cost for this state (dp[mask][pos] != -1), return it
    }
    int ans = INT_MAX; // Using predefined INT_MAX
    for (int city = 0; city < n; city++)
    {
        int cityBit = (1 << city);
        if ((mask & cityBit) == 0)  //that is atleast 1 is 0..unvisited..And table 1 & 1 =1 else all 0
        {
            int newAns = dist[pos][city] + tsp(mask | cityBit, city);
            ans = min(ans, newAns);
        }
    }
    return dp[mask][pos] = ans;
}
int main()
{
    for (int i = 0; i < (1 << n); i++)
    {
        for (int j = 0; j < n; j++)
        {
            dp[i][j] = -1;
        }
    }
    cout << "Minimum weight is: " << tsp(1, 0) << endl;
    return 0;
}

/*
tsp(1, 0): Start the TSP algorithm from city 0, with only city 0 visited.
 The initial mask is 1 (binary 0001), which means only city 0 is visited.
*/
//===============================================================================







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

