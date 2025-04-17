#include <iostream>
#include <vector>
using namespace std;

#define INF 9999

int shortestDist(vector<vector<int>> &graph)
{
    int n = graph.size();
    vector<int> cost(n, INF), path(n, -1);
    cost[n - 1] = 0;

    for (int i = n - 2; i >= 0; i--)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (graph[i][j] != INF && graph[i][j] + cost[j] < cost[i])
            {
                cost[i] = graph[i][j] + cost[j];
                path[i] = j;
            }
        }
    }

    cout << "Minimum cost: " << cost[0] << "\nPath: ";
    int i = 0;
    while (i != -1)
    {
        cout << i << " ";
        i = path[i];
    }
    cout << endl;
    return cost[0];
}

int main()
{
    int n;
    cout << "Enter number of vertices: ";
    cin >> n;
    vector<vector<int>> graph(n, vector<int>(n));
    cout << "Enter cost matrix (INF as 9999):\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            cin >> graph[i][j];
            if (graph[i][j] == 9999)
                graph[i][j] = INF;
        }
    shortestDist(graph);
    return 0;
}

/*
Test Input:
Enter number of vertices: 4
Enter cost matrix (INF as 9999):
9999 1 2 5
9999 9999 3 4
9999 9999 9999 2
9999 9999 9999 9999

Expected Output:
Minimum cost: 4
Path: 0 2 3
*/
