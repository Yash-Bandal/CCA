#include <bits/stdc++.h>
using namespace std;

// DisjointSet class to perform union-findPar with union by size
class DisjointSet
{
    vector<int> parent, size;
public:
    DisjointSet(int n)
    {
        parent.resize(n + 1);
        size.resize(n + 1);
        for (int i = 0; i <= n; i++)
        {
            parent[i] = i; //[1 2 3 4 5]
            size[i] = 1;   //[1 1 1 1 1]
        }
    }

    // findPar with path compression
    int findPar(int node)
    {
        if (node == parent[node])
            return node;
        return parent[node] = findPar(parent[node]);
    }

    // Union by size
    void unionBySize(int u, int v)
    {
        int rootU = findPar(u);
        int rootV = findPar(v);
        // base
        if (rootU == rootV)
            return;

        if (size[rootU] < size[rootV])
        {
            parent[rootU] = rootV;
            size[rootV] += size[rootU];
        }
        else
        {
            parent[rootV] = rootU;
            size[rootU] += size[rootV];
        }
    }
};


int spanningTree(int V, vector<vector<int>> adj[])
{
    vector<pair<int, pair<int, int>>> edges; //{wt , {node , adjnode}}
    for (int i = 0; i < V; i++)
    {
        for (auto it : adj[i])
        {
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

    vector<pair<int, int>> mstEdges; 

    for (auto it : edges)
    {
        int wt = it.first;
        int u = it.second.first;
        int v = it.second.second;

        if (ds.findPar(u) != ds.findPar(v))
        {
            mstWt += wt;
            mstEdges.push_back({u, v});
            ds.unionBySize(u, v);
        }
    }
    // Print edges included in the MST
    cout << "Edges in the MST:" << endl;
    for (auto edge : mstEdges)
    {
        cout << "(" << edge.first << ", " << edge.second << ") ";
    }
    cout << endl;

    return mstWt;
}

int main()
{
    int V = 5;
    vector<vector<int>> adj[V] = {
        {{1, 2}, {2, 1}},                 // adj[0]
        {{0, 2}, {2, 1}},                 // Node 1 has edges to node 0 (weight 2) and node 2 (weight 1)
        {{0, 1}, {1, 1}, {3, 2}, {4, 2}}, 
        {{2, 2}, {4, 1}},                 
        {{3, 1}, {2, 2}}                  
    };

    int mstWeight = spanningTree(V, adj);
    cout << "The sum of all the edge weights: " << mstWeight << endl;
    return 0;
}
