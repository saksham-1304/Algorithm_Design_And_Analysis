#include<bits/stdc++.h>
using namespace std;

void printParenthesis(int i, int j, vector<vector<int>> &bracket, char &name)
{
    if (i == j)
    {
        cout << name++;
        return;
    }
    cout << "(";
    printParenthesis(i, bracket[i][j], bracket, name);
    printParenthesis(bracket[i][j] + 1, j, bracket, name);
    cout << ")";
}

void matrixChainOrder(vector<int> &p, int n)
{
    vector<vector<int>> m(n, vector<int>(n, 0)), bracket(n, vector<int>(n, 0));

    for (int L = 2; L < n; L++)
        for (int i = 1; i < n - L + 1; i++)
        {
            int j = i + L - 1;
            m[i][j] = INT_MAX;
            for (int k = i; k < j; k++)
            {
                int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (q < m[i][j])
                {
                    m[i][j] = q;
                    bracket[i][j] = k;
                }
            }
        }

    cout << "Minimum number of multiplications: " << m[1][n - 1] << endl;
    cout << "Optimal Parenthesization: ";
    char name = 'A';
    printParenthesis(1, n - 1, bracket, name);
    cout << endl;
}

int main()
{
    int n;
    cout << "Enter number of matrices: ";
    cin >> n;
    vector<int> p(n + 1);
    cout << "Enter dimensions (length " << n + 1 << "): ";
    for (int i = 0; i <= n; i++)
        cin >> p[i];
    matrixChainOrder(p, n + 1);
    return 0;
}

// Test case (example input as comment):
// Input:
// 4
// 40 20 30 10 30
// Expected Output:
// Minimum number of multiplications: 26000
// Optimal Parenthesization: ((A(BC))D)
