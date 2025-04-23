#include <iostream>
#include <vector>
using namespace std;

bool isSafe(vector<string> &board, int row, int col, int n)
{
    for (int i = 0; i < col; i++)
        if (board[row][i] == 'Q')
            return false;

    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j] == 'Q')
            return false;

    for (int i = row, j = col; i < n && j >= 0; i++, j--)
        if (board[i][j] == 'Q')
            return false;

    return true;
}

void solveNQueens(vector<string> &board, int col, int n, int &solutionCount)
{
    if (col == n)
    {
        solutionCount++;
        for (int i = 0; i < n; i++)
            cout << board[i] << endl;
        cout << endl;
        return;
    }

    for (int i = 0; i < n; i++)
    {
        if (isSafe(board, i, col, n))
        {
            board[i][col] = 'Q';
            solveNQueens(board, col + 1, n, solutionCount);
            board[i][col] = '.';
        }
    }
}

int main()
{
    int n;
    cout << "Enter value of N for N-Queens: ";
    cin >> n;

    if (n <= 0)
    {
        cout << "Invalid input: N must be a positive integer." << endl;
        return 1;
    }

    vector<string> board(n, string(n, '.'));
    cout << n << "-Queens solutions:" << endl;

    // Add a solution counter
    int solutionCount = 0;

    // Call the modified function directly instead of using a lambda
    solveNQueens(board, 0, n, solutionCount);

    if (solutionCount == 0)
    {
        cout << "No solutions found for N=" << n << endl;
    }
    else
    {
        cout << "Total solutions found: " << solutionCount << endl;
    }

    return 0;
}

/*
Test Case:
Enter value of N for N-Queens: 4
4-Queens solutions:
.Q..
...Q
Q...
..Q.

..Q.
Q...
...Q
.Q..

Total solutions found: 2

Explanation:
- For N=4, there are exactly 2 solutions to the N-Queens problem
- Each solution represents a valid placement of 4 queens on a 4x4 chessboard
- In each solution, no queen can attack any other queen (i.e., no two queens share the same row, column, or diagonal)
- The output represents the board configuration where 'Q' is a queen and '.' is an empty cell
*/
