#include <bits/stdc++.h>
using namespace std;
vector<int> Sieve(int n)
{
    vector<int> A(n + 1);
    for (int p = 2; p <= n; ++p)
    {
        A[p] = p;
    }

    for (int p = 2; p <= sqrt(n); ++p)
    {
        if (A[p] != 0)
        {
            for (int j = p * p; j <= n; j += p)
            {
                A[j] = 0;
            }
        }
    }

    vector<int> L;
    for (int p = 2; p <= n; ++p)
    {
        if (A[p] != 0)
        {
            L.push_back(A[p]);
        }
    }
    return L;
}

int main()
{
    int n;
    cout << "Enter the value of n: ";
    cin >> n;

    if (n < 2)
    {
        cout << "There are no prime numbers less than 2." << endl;
        return 0;
    }

    vector<int> primes = Sieve(n);

    cout << "Prime numbers up to " << n << ": ";
    for (int prime : primes)
    {
        cout << prime << " ";
    }
    cout << endl;
    return 0;
}

/*
Time Complexity: 𝑂(𝑛⋅log(log(𝑛)))
Space Complexity: O(n)
*/