#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int spanningTreePrim(int V, vector<pair<int, int>> adj[]) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        vector<int> vis(V, 0);
        pq.push({0, 0});
        int sum = 0;
        while (!pq.empty()) {
            auto it = pq.top();
            pq.pop();
            int node = it.second;
            int wt = it.first;

            if (vis[node] == 1) continue;
            vis[node] = 1;
            sum += wt;
            for (auto it : adj[node]) {
                int adjNode = it.first;
                int edW = it.second;
                if (!vis[adjNode]) {
                    pq.push({edW, adjNode});
                }
            }
        }
        return sum;
    }
};

int main() {
    int V = 5;
    vector<pair<int, int>> adj[V];
    vector<vector<int>> edges = {{0, 1, 2}, {0, 2, 1}, {1, 2, 1}, {2, 3, 2}, {3, 4, 1}, {4, 2, 2}};
    for (auto it : edges) {
        int u = it[0];
        int v = it[1];
        int wt = it[2];
        adj[u].push_back({v, wt});
        adj[v].push_back({u, wt}); // Undirected graph
    }

    Solution obj;
    int primWt = obj.spanningTreePrim(V, adj);
    cout << "Prim's Algorithm: The sum of all the edge weights: " << primWt << endl;

    return 0;
}
