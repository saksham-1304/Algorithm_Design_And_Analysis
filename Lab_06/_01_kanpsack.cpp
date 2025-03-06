// Knapsack Problem Using Greedy Algorithm

#include <bits/stdc++.h>
using namespace std;
int main()
{
  int n, W;
  cout << "Enter number of items: ";
  cin >> n;
  cout << "Enter the capacity of the knapsack: ";
  cin >> W;

  vector<pair<int, int>> items(n);
  cout << "Enter the weight and value of each item: ";
  for (int i = 0; i < n; i++)
  {
    cin >> items[i].first >> items[i].second;
  }

  sort(items.begin(), items.end(), [](pair<int, int> a, pair<int, int> b)
       { return (double)a.second / a.first > (double)b.second / b.first; });

  double totalValue = 0;
  for (int i = 0; i < n; i++)
  {
    if (W == 0)
      break;
    int weight = min(W, items[i].first);
    totalValue += weight * (double)items[i].second / items[i].first;
    W -= weight;
  }

  cout << "Total value of items in the knapsack: " << totalValue << endl;

  return 0;
}
