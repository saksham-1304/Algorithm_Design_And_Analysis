#include <iostream>
#include <vector>
using namespace std;
unsigned long long catalanNumber(int n)
{
    vector<unsigned long long> dp(n + 1, 0);
    dp[0] = dp[1] = 1;

    for (int i = 2; i <= n; i++)
        for (int j = 0; j < i; j++)
            dp[i] += dp[j] * dp[i - j - 1];

    return dp[n];
}

int main()
{
    int n;
    cout << "Enter value of n for Catalan number: ";
    cin >> n;
    cout << "Catalan number at position " << n << " is " << catalanNumber(n) << endl;
    return 0;
}

/*
Enter value of n for Catalan number: 8
Catalan number at position 8 is 1430
*/