#include <iostream>
#include <vector>

using namespace std;

void addMatrix(vector<vector<int>> &A, vector<vector<int>> &B,
               vector<vector<int>> &C, int size)
{
  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++)
      C[i][j] = A[i][j] + B[i][j];
}

void subMatrix(vector<vector<int>> &A, vector<vector<int>> &B,
               vector<vector<int>> &C, int size)
{
  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++)
      C[i][j] = A[i][j] - B[i][j];
}

void strassen(vector<vector<int>> &A, vector<vector<int>> &B,
              vector<vector<int>> &C, int size)
{
  if (size == 1)
  {
    C[0][0] = A[0][0] * B[0][0];
    return;
  }

  int newSize = size / 2;
  vector<vector<int>> A11(newSize, vector<int>(newSize));
  vector<vector<int>> A12(newSize, vector<int>(newSize));
  vector<vector<int>> A21(newSize, vector<int>(newSize));
  vector<vector<int>> A22(newSize, vector<int>(newSize));
  vector<vector<int>> B11(newSize, vector<int>(newSize));
  vector<vector<int>> B12(newSize, vector<int>(newSize));
  vector<vector<int>> B21(newSize, vector<int>(newSize));
  vector<vector<int>> B22(newSize, vector<int>(newSize));

  for (int i = 0; i < newSize; i++)
    for (int j = 0; j < newSize; j++)
    {
      A11[i][j] = A[i][j];
      A12[i][j] = A[i][j + newSize];
      A21[i][j] = A[i + newSize][j];
      A22[i][j] = A[i + newSize][j + newSize];

      B11[i][j] = B[i][j];
      B12[i][j] = B[i][j + newSize];
      B21[i][j] = B[i + newSize][j];
      B22[i][j] = B[i + newSize][j + newSize];
    }

  vector<vector<int>> P1(newSize, vector<int>(newSize));
  vector<vector<int>> P2(newSize, vector<int>(newSize));
  vector<vector<int>> P3(newSize, vector<int>(newSize));
  vector<vector<int>> P4(newSize, vector<int>(newSize));
  vector<vector<int>> P5(newSize, vector<int>(newSize));
  vector<vector<int>> P6(newSize, vector<int>(newSize));
  vector<vector<int>> P7(newSize, vector<int>(newSize));
  vector<vector<int>> temp1(newSize, vector<int>(newSize));
  vector<vector<int>> temp2(newSize, vector<int>(newSize));

  addMatrix(A11, A22, temp1, newSize);
  addMatrix(B11, B22, temp2, newSize);
  strassen(temp1, temp2, P1, newSize);

  addMatrix(A21, A22, temp1, newSize);
  strassen(temp1, B11, P2, newSize);

  subMatrix(B12, B22, temp1, newSize);
  strassen(A11, temp1, P3, newSize);

  subMatrix(B21, B11, temp1, newSize);
  strassen(A22, temp1, P4, newSize);

  addMatrix(A11, A12, temp1, newSize);
  strassen(temp1, B22, P5, newSize);

  subMatrix(A21, A11, temp1, newSize);
  addMatrix(B11, B12, temp2, newSize);
  strassen(temp1, temp2, P6, newSize);

  subMatrix(A12, A22, temp1, newSize);
  addMatrix(B21, B22, temp2, newSize);
  strassen(temp1, temp2, P7, newSize);

  vector<vector<int>> C11(newSize, vector<int>(newSize));
  vector<vector<int>> C12(newSize, vector<int>(newSize));
  vector<vector<int>> C21(newSize, vector<int>(newSize));
  vector<vector<int>> C22(newSize, vector<int>(newSize));

  addMatrix(P1, P4, temp1, newSize);
  subMatrix(temp1, P5, temp2, newSize);
  addMatrix(temp2, P7, C11, newSize);

  addMatrix(P3, P5, C12, newSize);
  addMatrix(P2, P4, C21, newSize);

  addMatrix(P1, P3, temp1, newSize);
  subMatrix(temp1, P2, temp2, newSize);
  addMatrix(temp2, P6, C22, newSize);

  for (int i = 0; i < newSize; i++)
    for (int j = 0; j < newSize; j++)
    {
      C[i][j] = C11[i][j];
      C[i][j + newSize] = C12[i][j];
      C[i + newSize][j] = C21[i][j];
      C[i + newSize][j + newSize] = C22[i][j];
    }
}

int nextPowerOf2(int n)
{
  int power = 1;
  while (power < n)
    power *= 2;
  return power;
}

int main()
{
  int n;
  cout << "Enter matrix size n: ";
  cin >> n;

  int newSize = nextPowerOf2(n);
  vector<vector<int>> A(newSize, vector<int>(newSize, 0));
  vector<vector<int>> B(newSize, vector<int>(newSize, 0));
  vector<vector<int>> C(newSize, vector<int>(newSize, 0));

  cout << "Enter matrix A (" << n << "x" << n << "):\n";
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      cin >> A[i][j];

  cout << "Enter matrix B (" << n << "x" << n << "):\n";
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      cin >> B[i][j];

  strassen(A, B, C, newSize);

  cout << "Resultant Matrix C (" << n << "x" << n << "):\n";
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
      cout << C[i][j] << " ";
    cout << endl;
  }

  return 0;
}
