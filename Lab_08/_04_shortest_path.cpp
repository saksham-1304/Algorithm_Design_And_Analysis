#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define INF 1e9

void dijkstra(int src, int V, vector<vector<pair<int, int>>> &adj)
{
    vector<int> dist(V, INF);
    dist[src] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, src});

    while (!pq.empty())
    {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        for (auto &edge : adj[u])
        {
            int v = edge.first;
            int w = edge.second;

            if (dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    cout << "Shortest paths from " << src << ":\n";
    for (int i = 0; i < V; ++i)
        cout << "To " << i << ": " << dist[i] << "\n";
}

int main()
{
    int V, E, src;
    cout << "Enter number of vertices and edges: ";
    cin >> V >> E;

    vector<vector<pair<int, int>>> adj(V);
    cout << "Enter edges (u v weight):\n";
    for (int i = 0; i < E; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }

    cout << "Enter source vertex: ";
    cin >> src;

    dijkstra(src, V, adj);
    return 0;
}

/*
=== TEST CASE ===
Input:
Enter number of vertices and edges: 6 9
Enter edges (u v weight):
0 1 4
0 2 2
1 2 5
1 3 10
2 1 3
2 3 2
2 4 8
3 4 9
4 5 6
Enter source vertex: 0

Expected Output:
Shortest paths from 0:
To 0: 0
To 1: 4
To 2: 2
To 3: 4
To 4: 10
To 5: 16
*/
