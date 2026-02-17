#include <bits/stdc++.h>

using namespace std;

void dijkstra(int V, vector<vector<pair<int, int>>> &adj, int source) {
    vector<int> dist(V, INT_MAX);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    dist[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) {
        int currDist = pq.top().first;
        int node = pq.top().second;
        pq.pop();

        if (currDist > dist[node])
            continue;

        for (auto &edge : adj[node]) {
            int adjNode = edge.first;
            int weight = edge.second;

            if (currDist + weight < dist[adjNode]) {
                dist[adjNode] = currDist + weight;
                pq.push({dist[adjNode], adjNode});
            }
        }
    }
    cout << "Vertex\tDistance from Source " << source << endl;
    for (int i = 0; i < V; i++) {
        cout << i << "\t\t" << dist[i] << endl;
    }
}

int main() {
    int V, E;
    cout << "Enter number of vertices and edges: ";
    cin >> V >> E;

    vector<vector<pair<int, int>>> adj(V);

    cout << "Enter edges (u v w):\n";
    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    int source;
    cout << "Enter source vertex: ";
    cin >> source;

    dijkstra(V, adj, source);

    return 0;
}
