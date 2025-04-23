#include <bits/stdc++.h>
using namespace std;

#define INF INT_MAX
#define N 10 // Max number of cities

class TSPNode {
public:
    vector<vector<int>> reducedMatrix;
    vector<int> path;
    int cost, vertex, level;

    TSPNode(vector<vector<int>> mat, vector<int> p, int l, int v, int c) {
        reducedMatrix = mat;
        path = p;
        level = l;
        vertex = v;
        cost = c;
    }
};

int reduceMatrix(vector<vector<int>>& mat) {
    int reduction = 0;

    // Row reduction
    for (int i = 0; i < mat.size(); i++) {
        int rowMin = INF;
        for (int j = 0; j < mat.size(); j++)
            rowMin = min(rowMin, mat[i][j]);
        if (rowMin != INF && rowMin != 0) {
            reduction += rowMin;
            for (int j = 0; j < mat.size(); j++)
                if (mat[i][j] != INF)
                    mat[i][j] -= rowMin;
        }
    }

    // Column reduction
    for (int j = 0; j < mat.size(); j++) {
        int colMin = INF;
        for (int i = 0; i < mat.size(); i++)
            colMin = min(colMin, mat[i][j]);
        if (colMin != INF && colMin != 0) {
            reduction += colMin;
            for (int i = 0; i < mat.size(); i++)
                if (mat[i][j] != INF)
                    mat[i][j] -= colMin;
        }
    }

    return reduction;
}

struct CompareTSP {
    bool operator()(TSPNode* a, TSPNode* b) {
        return a->cost > b->cost;
    }
};

void solveTSP(vector<vector<int>> costMatrix, int start) {
    int n = costMatrix.size();

    priority_queue<TSPNode*, vector<TSPNode*>, CompareTSP> pq;

    vector<vector<int>> reducedMatrix = costMatrix;
    int cost = reduceMatrix(reducedMatrix);

    vector<int> path;
    path.push_back(start);

    TSPNode* root = new TSPNode(reducedMatrix, path, 0, start, cost);
    pq.push(root);

    while (!pq.empty()) {
        TSPNode* minNode = pq.top();
        pq.pop();

        if (minNode->level == n - 1) {
            minNode->path.push_back(start);
            cout << "Minimum cost path: ";
            for (int v : minNode->path) cout << v << " ";
            cout << "\nTotal cost: " << minNode->cost + costMatrix[minNode->vertex][start] << endl;
            return;
        }

        for (int i = 0; i < n; i++) {
            if (minNode->reducedMatrix[minNode->vertex][i] != INF) {
                vector<vector<int>> newMatrix = minNode->reducedMatrix;
                for (int k = 0; k < n; k++) {
                    newMatrix[minNode->vertex][k] = INF;
                    newMatrix[k][i] = INF;
                }
                newMatrix[i][start] = INF;

                int newCost = minNode->cost + minNode->reducedMatrix[minNode->vertex][i] + reduceMatrix(newMatrix);
                vector<int> newPath = minNode->path;
                newPath.push_back(i);

                TSPNode* child = new TSPNode(newMatrix, newPath, minNode->level + 1, i, newCost);
                pq.push(child);
            }
        }
    }
}

int main() {
    int n;
    cout << "Enter number of cities: ";
    cin >> n;

    vector<vector<int>> costMatrix(n, vector<int>(n));
    cout << "Enter cost matrix (enter -1 for no direct path):\n";
    for (int i=0; i<n; i++)
        for (int j=0; j<n; j++) {
            cin >> costMatrix[i][j];
            if (costMatrix[i][j] == -1)
                costMatrix[i][j] = INF;
        }

    int start = 0;
    cout << "Enter starting city (0-based index): ";
    cin >> start;

    solveTSP(costMatrix, start);
    return 0;
}
/*
 Test Input:
 Enter number of cities: 4
 Enter cost matrix (enter -1 for no direct path):
 0 10 15 20
 10 0 35 25
 15 35 0 30
 20 25 30 0
 Enter starting city (0-based index): 0
 Expected Output:
 Minimum cost path: 0 1 3 2 0
 Total cost: 80
*/
