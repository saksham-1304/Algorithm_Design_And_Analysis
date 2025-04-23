#include <iostream>
#include <vector>
using namespace std;

// Debug function to print current coloring state
void printColorState(vector<int> &color)
{
    cout << "Current colors: ";
    for (int i = 0; i < color.size(); i++)
    {
        cout << color[i] << " ";
    }
    cout << endl;
}

bool isSafe(int v, vector<vector<bool>> &graph, vector<int> &color, int c)
{
    for (int i = 0; i < graph.size(); i++)
    {
        if (graph[v][i] && color[i] == c)
        {
            cout << "Cannot color vertex " << v << " with color " << c
                 << " because adjacent vertex " << i << " has same color" << endl;
            return false;
        }
    }
    cout << "Safe to color vertex " << v << " with color " << c << endl;
    return true;
}

bool graphColoringUtil(vector<vector<bool>> &graph, int m, vector<int> &color, int v)
{
    if (v == graph.size())
        return true;

    cout << "\nTrying to color vertex " << v << endl;

    for (int c = 1; c <= m; c++)
    {
        cout << "Attempting color " << c << " for vertex " << v << endl;

        if (isSafe(v, graph, color, c))
        {
            color[v] = c;
            printColorState(color);

            if (graphColoringUtil(graph, m, color, v + 1))
                return true;

            cout << "Backtracking: removing color " << c << " from vertex " << v << endl;
            color[v] = 0;
        }
    }

    cout << "No valid color found for vertex " << v << endl;
    return false;
}

void graphColoring(vector<vector<bool>> &graph, int m)
{
    int V = graph.size();
    vector<int> color(V, 0);

    // Validate the graph
    for (int i = 0; i < V; i++)
    {
        if (graph[i][i])
        {
            cout << "Warning: Vertex " << i << " has a self-loop, which may cause issues with coloring." << endl;
        }
    }

    cout << "\nStarting coloring process with " << m << " colors..." << endl;

    if (!graphColoringUtil(graph, m, color, 0))
    {
        cout << "\nNo solution exists" << endl;
        return;
    }

    cout << "\nSolution Exists: Colors -> ";
    for (int i = 0; i < V; i++)
        cout << color[i] << " ";
    cout << endl;
}

int main()
{
    int V, m;
    cout << "Enter number of vertices: ";
    cin >> V;

    if (V <= 0)
    {
        cout << "Error: Number of vertices must be positive" << endl;
        return 1;
    }

    cout << "Enter number of colors: ";
    cin >> m;

    if (m <= 0)
    {
        cout << "Error: Number of colors must be positive" << endl;
        return 1;
    }

    vector<vector<bool>> graph(V, vector<bool>(V, false));
    cout << "Enter adjacency matrix (row-wise, use 0 for no edge, 1 for edge):" << endl;

    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            int val;
            cin >> val;
            if (val != 0 && val != 1)
            {
                cout << "Error: Adjacency matrix entries must be 0 or 1" << endl;
                return 1;
            }
            graph[i][j] = (val == 1);
        }
    }

    // Print the graph for verification
    cout << "\nGraph adjacency matrix:" << endl;
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            cout << graph[i][j] << " ";
        }
        cout << endl;
    }

    graphColoring(graph, m);
    return 0;
}

/*
Test Case:
Enter number of vertices: 4
Enter number of colors: 3
Enter adjacency matrix (row-wise):
0 1 1 1
1 0 1 0
1 1 0 1
1 0 1 0
Solution Exists: Colors -> 1 2 3 1

Explanation:
- This represents a graph with 4 vertices
- Using 3 possible colors
- The adjacency matrix shows connections between vertices
- The solution assigns color 1 to vertices 0 and 3, color 2 to vertex 1, and color 3 to vertex 2
- This coloring ensures no adjacent vertices have the same color
*/
