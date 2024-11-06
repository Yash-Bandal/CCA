Time Complexity: 𝑂 ( 𝑛^2 ⋅ 2 𝑛 )
    Space Complexity: 𝑂 ( 𝑛 ⋅ 2 𝑛 )

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

int n = 4;
int dp[16][4];
int parent[16][4];  // To track the next city in the path
int dist[10][10] = {
    {0, 20, 42, 25},
    {20, 0, 30, 34},
    {42, 30, 0, 10},
    {25, 34, 10, 0}
};
int VisitedAll = (1 << n) - 1; 

int tsp(int mask, int pos) {
    if (mask == VisitedAll) { 
        return dist[pos][0];  // Distance back to the start city
    }
    if (dp[mask][pos] != -1) {
        return dp[mask][pos];  // Return the stored result if already computed
    }
    
    int ans = INT_MAX;
    int nextCity = -1;  // To store the city that gives the minimum cost
    
    for (int city = 0; city < n; city++) {
        int cityBit = (1 << city);
        if ((mask & cityBit) == 0) {  // If city is unvisited
            int newAns = dist[pos][city] + tsp(mask | cityBit, city);
            if (newAns < ans) {
                ans = newAns;
                nextCity = city;  // Update the next city in the path
            }
        }
    }
    
    parent[mask][pos] = nextCity;  // Store the next city in the parent array
    return dp[mask][pos] = ans;
}

void printPath() {
    int mask = 1, pos = 0;
    cout << "Path: " << pos;  // Starting from city 0
    
    while (mask != VisitedAll) {
        pos = parent[mask][pos];  // Get the next city in the path
        cout << " -> " << pos;
        mask |= (1 << pos);  // Mark this city as visited in the mask
    }
    cout << " -> 0" << endl;  // Return to the starting city
}

int main() {
    for (int i = 0; i < (1 << n); i++) {
        for (int j = 0; j < n; j++) {
            dp[i][j] = -1;
            parent[i][j] = -1;  // Initialize the parent array
        }
    }
    
    cout << "Minimum weight is: " << tsp(1, 0) << endl;
    printPath();  // Print the path
    
    return 0;
}
