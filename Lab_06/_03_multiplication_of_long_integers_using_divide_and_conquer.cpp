#include <bits/stdc++.h>
using namespace std;

// Function to add two large numbers
string addStrings(string num1, string num2)
{
  string result = "";
  int carry = 0, sum;
  int i = num1.size() - 1, j = num2.size() - 1;

  while (i >= 0 || j >= 0 || carry)
  {
    sum = carry;
    if (i >= 0)
      sum += num1[i--] - '0';
    if (j >= 0)
      sum += num2[j--] - '0';
    result.push_back(sum % 10 + '0');
    carry = sum / 10;
  }

  reverse(result.begin(), result.end());
  return result;
}

// Function to multiply a number by a power of 10 (appending zeroes)
string multiplyByPowerOf10(string num, int power)
{
  return num + string(power, '0');
}

// Function to subtract two large numbers (num1 > num2 always assumed)
string subtractStrings(string num1, string num2)
{
  string result = "";
  int borrow = 0, diff;
  int i = num1.size() - 1, j = num2.size() - 1;

  while (i >= 0)
  {
    diff = (num1[i] - '0') - (j >= 0 ? (num2[j--] - '0') : 0) - borrow;
    if (diff < 0)
    {
      diff += 10;
      borrow = 1;
    }
    else
    {
      borrow = 0;
    }
    result.push_back(diff + '0');
    i--;
  }

  while (result.size() > 1 && result.back() == '0')
    result.pop_back();
  reverse(result.begin(), result.end());
  return result;
}

// Recursive function to multiply two large numbers using Karatsuba algorithm
string karatsubaMultiply(string X, string Y)
{
  int n = max(X.size(), Y.size());

  // Base case: Single-digit multiplication
  if (n == 1)
  {
    int product = (X[0] - '0') * (Y[0] - '0');
    return to_string(product);
  }

  // Padding numbers with leading zeros to make them of equal length
  while (X.size() < n)
    X = "0" + X;
  while (Y.size() < n)
    Y = "0" + Y;

  int m = n / 2;

  // Splitting the numbers
  string A = X.substr(0, n - m);
  string B = X.substr(n - m);
  string C = Y.substr(0, n - m);
  string D = Y.substr(n - m);

  // Recursive multiplications
  string AC = karatsubaMultiply(A, C);
  string BD = karatsubaMultiply(B, D);
  string AplusB = addStrings(A, B);
  string CplusD = addStrings(C, D);
  string midTerm = karatsubaMultiply(AplusB, CplusD);
  midTerm = subtractStrings(midTerm, addStrings(AC, BD));

  // Compute final result using Karatsuba formula
  return addStrings(addStrings(multiplyByPowerOf10(AC, 2 * m), multiplyByPowerOf10(midTerm, m)), BD);
}

// Driver function
int main()
{
  string num1, num2;
  cout << "Enter first large number: ";
  cin >> num1;
  cout << "Enter second large number: ";
  cin >> num2;

  cout << "Product: " << karatsubaMultiply(num1, num2) << endl;
  return 0;
}