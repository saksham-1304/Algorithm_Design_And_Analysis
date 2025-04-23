#include <bits/stdc++.h>
using namespace std;

#define N 4

// Direction vectors: Down, Left, Right, Up
int rowDir[] = {1, 0, 0, -1};
int colDir[] = {0, -1, 1, 0};

class PuzzleNode
{
public:
    vector<vector<int>> mat;
    int x, y, cost, level;
    PuzzleNode *parent;

    PuzzleNode(vector<vector<int>> m, int x, int y, int newLevel, PuzzleNode *p, const vector<vector<int>> &finalState)
    {
        this->mat = m;
        this->x = x;
        this->y = y;
        this->level = newLevel;
        this->parent = p;
        this->cost = calculateCost(finalState);
    }

    int calculateCost(const vector<vector<int>> &finalState)
    {
        int count = 0;
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                if (mat[i][j] && mat[i][j] != finalState[i][j])
                    count++;
        return count;
    }

    bool isSafe(int x, int y)
    {
        return (x >= 0 && x < N && y >= 0 && y < N);
    }
};

struct CompareCost
{
    bool operator()(PuzzleNode *a, PuzzleNode *b)
    {
        return (a->cost + a->level) > (b->cost + b->level);
    }
};

void printPath(PuzzleNode *node)
{
    if (node == nullptr)
        return;
    printPath(node->parent);
    for (auto &row : node->mat)
    {
        for (int val : row)
            cout << val << " ";
        cout << endl;
    }
    cout << "----" << endl;
}

void solve15Puzzle(vector<vector<int>> &start, vector<vector<int>> &goal, int x, int y)
{
    priority_queue<PuzzleNode *, vector<PuzzleNode *>, CompareCost> pq;
    PuzzleNode *root = new PuzzleNode(start, x, y, 0, nullptr, goal);
    pq.push(root);

    while (!pq.empty())
    {
        PuzzleNode *minNode = pq.top();
        pq.pop();

        if (minNode->cost == 0)
        {
            cout << "Solution path:" << endl;
            printPath(minNode);
            return;
        }

        for (int i = 0; i < 4; i++)
        {
            int newX = minNode->x + rowDir[i];
            int newY = minNode->y + colDir[i];
            if (minNode->isSafe(newX, newY))
            {
                auto newMat = minNode->mat;
                swap(newMat[minNode->x][minNode->y], newMat[newX][newY]);
                PuzzleNode *child = new PuzzleNode(newMat, newX, newY, minNode->level + 1, minNode, goal);
                pq.push(child);
            }
        }
    }
}

int main()
{
    vector<vector<int>> start(N, vector<int>(N));
    vector<vector<int>> goal(N, vector<int>(N));
    int x, y;

    cout << "Enter initial configuration (use 0 for blank):\n";
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        {
            cin >> start[i][j];
            if (start[i][j] == 0)
            {
                x = i;
                y = j;
            }
        }

    cout << "Enter goal configuration:\n";
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> goal[i][j];

    solve15Puzzle(start, goal, x, y);
    return 0;
}

/*
Test Case:

Enter initial configuration (use 0 for blank):
1 2 3 4
5 6 0 8
9 10 7 11
13 14 15 12

Enter goal configuration:
1 2 3 4
5 6 7 8
9 10 11 12
13 14 15 0

Solution path:
1 2 3 4
5 6 0 8
9 10 7 11
13 14 15 12
----
1 2 3 4
5 6 7 8
9 10 0 11
13 14 15 12
----
1 2 3 4
5 6 7 8
9 10 11 0
13 14 15 12
----
1 2 3 4
5 6 7 8
9 10 11 12
13 14 15 0
----

Explanation:
- Initial state has the blank (0) in the middle row, and numbers 7, 8, 11, 12 out of position
- Goal state has the blank in the bottom right corner with all numbers in order
- The solution shows the sequence of moves to reach the goal:
  1. Start with initial state
  2. Move blank down to swap with 7
  3. Move blank right to swap with 11
  4. Move blank right to swap with 12
  5. Goal state reached
*/
