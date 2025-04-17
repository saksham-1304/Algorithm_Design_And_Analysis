#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef pair<int, int> pii;
const int INF = 1e9;

void primMST(int V, vector<vector<pii>> &graph)
{
    vector<int> key(V, INF), parent(V, -1);
    vector<bool> inMST(V, false);
    priority_queue<pii, vector<pii>, greater<>> pq;

    key[0] = 0;
    pq.push({0, 0});

    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();

        // Skip if vertex already included in MST
        if (inMST[u])
            continue;

        inMST[u] = true;

        for (auto &edge : graph[u])
        {
            int v = edge.first;
            int weight = edge.second;

            if (!inMST[v] && weight < key[v])
            {
                parent[v] = u;
                key[v] = weight;
                pq.push({key[v], v});
            }
        }
    }

    // Calculate total MST weight
    int totalWeight = 0;
    for (int i = 1; i < V; i++)
    {
        if (parent[i] != -1)
        {
            totalWeight += key[i];
        }
    }

    cout << "Prim's MST:\n";
    for (int i = 1; i < V; i++)
    {
        if (parent[i] != -1)
        {
            cout << parent[i] << " - " << i << " (weight: " << key[i] << ")\n";
        }
        else if (key[i] == INF)
        {
            cout << "Vertex " << i << " is not connected to the MST\n";
        }
    }

    cout << "Total MST Weight: " << totalWeight << endl;
}

int main()
{
    int V, E;
    cout << "Enter number of vertices and edges: ";
    cin >> V >> E;

    // Input validation
    if (V <= 0 || E < 0)
    {
        cout << "Invalid input: Number of vertices must be positive and edges non-negative\n";
        return 1;
    }

    vector<vector<pii>> graph(V);
    cout << "Enter edges (u v weight):\n";
    for (int i = 0; i < E; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;

        // Validate vertex indices and weight
        if (u < 0 || u >= V || v < 0 || v >= V)
        {
            cout << "Invalid vertices: must be between 0 and " << (V - 1) << endl;
            i--; // Retry this edge
            continue;
        }
        if (w < 0)
        {
            cout << "Warning: Negative weight detected. MST algorithms typically assume non-negative weights.\n";
        }

        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }

    primMST(V, graph);
    return 0;
}

/*
Test Input Example:

Input:
5 7
0 1 2
0 3 6
1 2 3
1 3 8
1 4 5
2 4 7
3 4 9

This represents a graph with 5 vertices and 7 edges:
- Edge from vertex 0 to 1 with weight 2
- Edge from vertex 0 to 3 with weight 6
- Edge from vertex 1 to 2 with weight 3
- Edge from vertex 1 to 3 with weight 8
- Edge from vertex 1 to 4 with weight 5
- Edge from vertex 2 to 4 with weight 7
- Edge from vertex 3 to 4 with weight 9

Expected Output:
Prim's MST:
0 - 1 (weight: 2)
1 - 2 (weight: 3)
0 - 3 (weight: 6)
1 - 4 (weight: 5)
Total MST Weight: 16
*/