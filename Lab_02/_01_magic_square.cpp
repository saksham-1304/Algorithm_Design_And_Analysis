#include <iostream>
#include <vector>
using namespace std;

// Function to check if a given magic square is valid
bool isMagicSquare(int size, vector<vector<int>> &matrix)
{
    int magicSum = size * (size * size + 1) / 2;

    // Check sum of each row and column
    for (int i = 0; i < size; i++)
    {
        int sumRow = 0, sumCol = 0;
        for (int j = 0; j < size; j++)
        {
            sumRow += matrix[i][j];
            sumCol += matrix[j][i];
        }
        if (sumRow != magicSum || sumCol != magicSum)
            return false;
    }

    // Check diagonals
    int sumMainDiagonal = 0, sumAntiDiagonal = 0;
    for (int i = 0; i < size; i++)
    {
        sumMainDiagonal += matrix[i][i];
        sumAntiDiagonal += matrix[i][size - i - 1];
    }

    return (sumMainDiagonal == magicSum && sumAntiDiagonal == magicSum);
}

// Function to print the magic square
void printMatrix(int size, vector<vector<int>> &matrix)
{
    cout << "\nMagic Square:\n";
    for (const auto &row : matrix)
    {
        for (int num : row)
        {
            cout << num << "\t";
        }
        cout << endl;
    }
}

// Function to generate an odd order magic square using the top-left approach
void generateOddMagicSquare(int size, vector<vector<int>> &matrix)
{
    int row = 0, col = size / 2;
    for (int num = 1; num <= size * size; num++)
    {
        matrix[row][col] = num;
        int newRow = (row - 1 + size) % size;
        int newCol = (col - 1 + size) % size;
        if (matrix[newRow][newCol] != 0)
        {
            row = (row + 1) % size;
        }
        else
        {
            row = newRow;
            col = newCol;
        }
    }
}

// Function to generate a doubly even magic square (size divisible by 4)
void generateDoublyEvenMagicSquare(int size, vector<vector<int>> &matrix)
{
    int num = 1;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            matrix[i][j] = num++;
        }
    }

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if ((i % 4 == j % 4) || ((i + j) % 4 == 3))
            {
                matrix[i][j] = size * size + 1 - matrix[i][j];
            }
        }
    }
}

// Function to generate a singly even magic square (4n+2 case) using the Strachey LUX method
void generateSinglyEvenMagicSquare(int size, vector<vector<int>> &matrix)
{
    int n = size / 2;
    vector<vector<int>> subSquare(n, vector<int>(n, 0));
    generateOddMagicSquare(n, subSquare);

    // Copy 4 sub-squares into the main matrix
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            matrix[i][j] = subSquare[i][j];
            matrix[i + n][j + n] = subSquare[i][j] + n * n;
            matrix[i][j + n] = subSquare[i][j] + 2 * n * n;
            matrix[i + n][j] = subSquare[i][j] + 3 * n * n;
        }
    }

    // Swap values to adjust for singly even case
    int k = (size - 2) / 4;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < k; j++)
        {
            swap(matrix[i][j], matrix[i + n][j]);
        }
        for (int j = size - k + 1; j < size; j++)
        {
            swap(matrix[i][j], matrix[i + n][j]);
        }
    }
    swap(matrix[n / 2][0], matrix[n / 2 + n][0]);
    swap(matrix[n / 2][k], matrix[n / 2 + n][k]);
}

int main()
{
    int size;
    cout << "Enter the size of the magic square: ";
    cin >> size;

    // Initialize matrix with 0
    vector<vector<int>> magicSquare(size, vector<int>(size, 0));

    // Generate magic square based on size type
    if (size % 2 == 1)
    {
        generateOddMagicSquare(size, magicSquare);
    }
    else if (size % 4 == 0)
    {
        generateDoublyEvenMagicSquare(size, magicSquare);
    }
    else
    {
        generateSinglyEvenMagicSquare(size, magicSquare);
    }

    // Print and validate the magic square
    printMatrix(size, magicSquare);
    cout << (isMagicSquare(size, magicSquare) ? "Valid Magic Square!" : "Invalid Magic Square!") << endl;

    return 0;
}