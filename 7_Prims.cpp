#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    int spanningTree(int V, vector<vector<int>> adj[]) {

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        
        vector<int> vis(V, 0); 
        vector<int> parent(V, -1); 
        vector<pair<int, int>> mstEdges; // Vector to store MST edges
        pq.push({0, 0}); 
        int sum = 0; 

        while (!pq.empty()) {
            auto it = pq.top();  //stores as pair{wt,node}
            pq.pop();
            int wt = it.first;    
            int node = it.second; 

            if (vis[node]) continue; 

            //else

            vis[node] = 1; 
            sum += wt;   

            for (auto it : adj[node]) {
                int adjNode = it[0]; // Adjacent node
                int edW = it[1];      // Weight of the edge

           
                if (!vis[adjNode]) {
                    pq.push({edW, adjNode}); // Push {weight, adjacent node}
                    parent[adjNode] = node; // Update parent
                                        // Store the edge (node, adjacent node) with its weight in the MST
                    mstEdges.push_back({node, adjNode});
                }
            }
        }
                // Print the edges in the Minimum Spanning Tree (MST)
        cout << "Edges in the Minimum Spanning Tree (MST):" << endl;
        for (auto edge : mstEdges) {
            cout << "(" << edge.first << ", " << edge.second << ") ";
        }
        cout << endl;
        

        return sum; 
    }

};

int main() {
    int V = 5; 

    vector<vector<int>> adj[] = {
        {{1, 2}, {2, 1}},  // Edges from node 0
        {{0, 2}, {2, 1}},  // Edges from node 1
        {{0, 1}, {1, 1}, {3, 2}, {4, 2}}, // Edges from node 2
        {{2, 2}, {4, 1}},  // Edges from node 3
        {{3, 1}, {2, 2}}   // Edges from node 4
    };

    Solution obj;
    int sum = obj.spanningTree(V, adj);
    cout << "The sum of all the edge weights: " << sum << endl;

    return 0;
}
