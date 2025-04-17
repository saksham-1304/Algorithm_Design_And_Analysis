#include <iostream>
#include <vector>
using namespace std;

#define INF 1e9

void floydWarshall(vector<vector<int>> &graph, int V)
{
    vector<vector<int>> dist = graph;

    for (int k = 0; k < V; k++)
        for (int i = 0; i < V; i++)
            for (int j = 0; j < V; j++)
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];

    cout << "All Pairs Shortest Paths:\n";
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            if (dist[i][j] >= INF)
                cout << "INF ";
            else
                cout << dist[i][j] << " ";
        }
        cout << endl;
    }
}

int main()
{
    int V;
    cout << "Enter number of vertices: ";
    cin >> V;
    vector<vector<int>> graph(V, vector<int>(V));
    cout << "Enter adjacency matrix (INF as 9999):\n";
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
        {
            cin >> graph[i][j];
            if (graph[i][j] == 9999)
                graph[i][j] = INF;
        }
    floydWarshall(graph, V);
    return 0;
}

/*
Test Input:
Enter number of vertices: 4
Enter adjacency matrix (INF as 9999):
0 3 9999 7
8 0 2 9999
5 9999 0 1
2 9999 9999 0

Expected Output:
All Pairs Shortest Paths:
0 3 5 7
8 0 2 3
5 8 0 1
2 5 7 0
*/
