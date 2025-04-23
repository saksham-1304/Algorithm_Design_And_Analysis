#include <bits/stdc++.h>
using namespace std;

class Item {
public:
    int weight, profit;
    double ratio;
    Item(int w, int p) : weight(w), profit(p) {
        ratio = (double)p / w;
    }
};

class Node {
public:
    int level, profit, weight;
    double bound;

    Node(int l, int p, int w) : level(l), profit(p), weight(w), bound(0.0) {}
};

bool cmp(Item a, Item b) {
    return a.ratio > b.ratio;
}

double bound(Node* u, int n, int W, vector<Item>& items) {
    if (u->weight >= W)
        return 0;

    double profit_bound = u->profit;
    int j = u->level + 1;
    int totalWeight = u->weight;

    while (j < n && totalWeight + items[j].weight <= W) {
        totalWeight += items[j].weight;
        profit_bound += items[j].profit;
        j++;
    }

    if (j < n)
        profit_bound += (W - totalWeight) * items[j].ratio;

    return profit_bound;
}

int knapsackBranchAndBound(int W, vector<Item>& items) {
    sort(items.begin(), items.end(), cmp);
    int n = items.size();

    queue<Node*> Q;
    Node* u = new Node(-1, 0, 0);
    u->bound = bound(u, n, W, items);
    Q.push(u);

    int maxProfit = 0;

    while (!Q.empty()) {
        Node* v = Q.front(); Q.pop();
        if (v->level == n - 1) continue;

        Node* u = new Node(v->level + 1, v->profit + items[v->level + 1].profit, v->weight + items[v->level + 1].weight);

        if (u->weight <= W && u->profit > maxProfit)
            maxProfit = u->profit;

        u->bound = bound(u, n, W, items);
        if (u->bound > maxProfit)
            Q.push(u);

        u = new Node(v->level + 1, v->profit, v->weight);
        u->bound = bound(u, n, W, items);
        if (u->bound > maxProfit)
            Q.push(u);
    }

    return maxProfit;
}

int main() {
    int n, W;
    cout << "Enter number of items: ";
    cin >> n;

    vector<Item> items;
    cout << "Enter weight and profit for each item:\n";
    for (int i = 0; i < n; ++i) {
        int w, p;
        cin >> w >> p;
        items.emplace_back(w, p);
    }

    cout << "Enter maximum capacity of knapsack: ";
    cin >> W;

    int maxProfit = knapsackBranchAndBound(W, items);
    cout << "Maximum Profit: " << maxProfit << endl;

    return 0;
}
/* 
Test case:
 Enter number of items: 4
 Enter weight and profit for each item:
 2 3
 3 4
 4 5
 5 6
 Enter maximum capacity of knapsack: 5
 Maximum Profit: 7
 Expected Output:
 Maximum Profit: 7
*/