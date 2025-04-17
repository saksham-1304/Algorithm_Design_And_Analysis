#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge
{
    int u, v, weight;
    bool operator<(Edge const &other) const
    {
        return weight < other.weight;
    }
};

int find(int u, vector<int> &parent)
{
    if (parent[u] != u)
        parent[u] = find(parent[u], parent);
    return parent[u];
}

void unite(int u, int v, vector<int> &parent, vector<int> &rank)
{
    u = find(u, parent);
    v = find(v, parent);
    if (u != v)
    {
        if (rank[u] < rank[v])
            swap(u, v);
        parent[v] = u;
        if (rank[u] == rank[v])
            rank[u]++;
    }
}

void kruskalMST(int V, vector<Edge> &edges)
{
    sort(edges.begin(), edges.end());
    vector<int> parent(V), rank(V, 0);
    for (int i = 0; i < V; i++)
        parent[i] = i;

    cout << "Kruskal's MST:\n";
    for (Edge &e : edges)
    {
        if (find(e.u, parent) != find(e.v, parent))
        {
            cout << e.u << " - " << e.v << " (" << e.weight << ")\n";
            unite(e.u, e.v, parent, rank);
        }
    }
}

int main()
{
    int V, E;
    cout << "Enter number of vertices and edges: ";
    cin >> V >> E;

    vector<Edge> edges(E);
    cout << "Enter edges (u v weight):\n";
    for (int i = 0; i < E; i++)
        cin >> edges[i].u >> edges[i].v >> edges[i].weight;

    kruskalMST(V, edges);
    return 0;
}


/* Sample Input:
6 9
0 1 4
0 2 4
1 2 2
1 3 3
1 4 4
2 4 3
3 4 2
3 5 3
4 5 3
*/

/* Sample Output:
Kruskal's MST:
1 - 2 (2)
3 - 4 (2)
1 - 3 (3)
2 - 4 (3)
3 - 5 (3)
*/
