#include <bits/stdc++.h>
using namespace std;

// DisjointSet class to perform union-findPar with union by size
class DisjointSet {
    vector<int> parent, size;

public:
    DisjointSet(int n) {
        parent.resize(n + 1);
        size.resize(n + 1);
        for (int i = 0; i <= n; i++) {
            parent[i] = i;           //[1 2 3 4 5]
            size[i] = 1;             //[1 1 1 1 1]
        }
    }

    // findPar with path compression
    int findPar(int node) {
        if (node == parent[node])
            return node;
        return parent[node] = findPar(parent[node]);
    }

    // Union by size
    void unionBySize(int u, int v) {
        int rootU = findPar(u);
        int rootV = findPar(v);
         //base
        if (rootU == rootV) return;

        if (size[rootU] < size[rootV]) {
            parent[rootU] = rootV;
            size[rootV] += size[rootU];
        } else {
            parent[rootV] = rootU;
            size[rootU] += size[rootV];
        }
    }
};


class Solution
{
public:
    //Function to find sum of weights of edges of the Minimum Spanning Tree.
    int spanningTree(int V, vector<vector<int>> adj[])
    {
        // 1 - 2 wt = 5
        /// 1 - > (2, 5)
        // 2 -> (1, 5)

        // 5, 1, 2
        // 5, 2, 1
        vector<pair<int, pair<int, int>>> edges;
        for (int i = 0; i < V; i++) {
            for (auto it : adj[i]) {
                int adjNode = it[0];
                int wt = it[1];
                int node = i;
                //{node adjnode wt}

                edges.push_back({wt, {node, adjNode}});
            }
        }
        DisjointSet ds(V);
        sort(edges.begin(), edges.end());
        int mstWt = 0;
        for (auto it : edges) {
            int wt = it.first;
            int u = it.second.first;
            int v = it.second.second;

            if (ds.findPar(u) != ds.findPar(v)) {
                mstWt += wt;
                ds.unionBySize(u, v);
            }
        }

        return mstWt;
    }
};

int main() {
    int V = 5;

    // Directly defining adj with edges
    vector<vector<int>> adj[V] = {
        {{1, 2}, {2, 1}}, //adj[0]
        {{0, 2}, {2, 1}}, // Node 1 has edges to node 0 (weight 2) and node 2 (weight 1)
        {{0, 1}, {1, 1}, {3, 2}, {4, 2}}, // Node 2 has edges to nodes 0, 1, 3, and 4
        {{2, 2}, {4, 1}}, // Node 3 has edges to node 2 (weight 2) and node 4 (weight 1)
        {{3, 1}, {2, 2}}  // Node 4 has edges to node 3 (weight 1) and node 2 (weight 2)
    };

    Solution obj;
    int mstWeight = obj.spanningTree(V, adj);
    cout << "The sum of all the edge weights: " << mstWeight << endl;
    return 0;
}
