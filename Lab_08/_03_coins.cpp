#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Sort coins and their counts together in increasing order
void sortCoins(vector<int> &coins, vector<int> &count)
{
    vector<pair<int, int>> paired;
    for (int i = 0; i < coins.size(); i++)
    {
        paired.push_back({coins[i], count[i]});
    }
    sort(paired.begin(), paired.end());

    for (int i = 0; i < coins.size(); i++)
    {
        coins[i] = paired[i].first;
        count[i] = paired[i].second;
    }
}

// Greedy change-making with unlimited supply
void changeUnlimited(int amount, const vector<int> &coins)
{
    cout << "Change with Unlimited Coins:\n";
    for (int i = coins.size() - 1; i >= 0; i--)
    {
        while (amount >= coins[i])
        {
            cout << coins[i] << " ";
            amount -= coins[i];
        }
    }
    if (amount > 0)
        cout << "\nCannot make exact change!";
    cout << "\n";
}

// Greedy change-making with limited supply
void changeLimited(int amount, const vector<int> &coins, vector<int> count)
{
    cout << "Change with Limited Coins:\n";
    for (int i = coins.size() - 1; i >= 0; i--)
    {
        while (amount >= coins[i] && count[i] > 0)
        {
            cout << coins[i] << " ";
            amount -= coins[i];
            count[i]--;
        }
    }
    if (amount > 0)
        cout << "\nCannot make exact change!";
    cout << "\n";
}

int main()
{
    vector<int> coins = {1, 5, 10, 20, 50, 100, 200, 500, 2000}; // paise
    vector<int> count(coins.size());

    int amount;
    cout << "Enter amount in paise to make change for: ";
    cin >> amount;

    cout << "Enter available quantity of each coin type:\n";
    for (int i = 0; i < coins.size(); i++)
    {
        cout << coins[i] << "p: ";
        cin >> count[i];
    }

    sortCoins(coins, count); // sort for greedy use

    changeUnlimited(amount, coins);
    changeLimited(amount, coins, count);

    return 0;
}

/*
=== TEST CASE 1 ===
Input:
Enter amount in paise to make change for: 546
Enter available quantity of each coin type:
1p: 10
5p: 10
10p: 10
20p: 5
50p: 5
100p: 5
200p: 3
500p: 1
2000p: 0

Output:
Change with Unlimited Coins:
500 20 20 5 1
Change with Limited Coins:
500 20 20 5 1

*/