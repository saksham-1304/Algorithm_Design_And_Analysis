// Defective Coin

#include <iostream>
#include <vector>
using namespace std;

void findDefectiveCoin(vector<int> &coins, int left, int right, bool &found, int &defectiveIndex, string &defectType)
{
    if (left > right || found)
        return;

    int n = right - left + 1;
    if (n == 1)
    {
        found = true;
        defectiveIndex = left;
        return;
    }

    int mid1 = left + n / 3;
    int mid2 = left + 2 * (n / 3);

    // Weigh two parts
    int leftSum = 0, rightSum = 0;
    for (int i = left; i < mid1; i++)
        leftSum += coins[i];
    for (int i = mid1; i < mid2; i++)
        rightSum += coins[i];

    if (leftSum == rightSum)
    {
        // Defective coin must be in the last part
        findDefectiveCoin(coins, mid2, right, found, defectiveIndex, defectType);
    }
    else if (leftSum < rightSum)
    {
        // Defective coin is in the left part and is lighter
        defectType = "Lighter";
        findDefectiveCoin(coins, left, mid1 - 1, found, defectiveIndex, defectType);
    }
    else
    {
        // Defective coin is in the right part and is heavier
        defectType = "Heavier";
        findDefectiveCoin(coins, mid1, mid2 - 1, found, defectiveIndex, defectType);
    }
}

int main()
{
    vector<int> coins = {10, 10, 10, 9, 10, 10, 10}; // Coin weights (one defective)

    bool found = false;
    int defectiveIndex = -1;
    string defectType = "";

    findDefectiveCoin(coins, 0, coins.size() - 1, found, defectiveIndex, defectType);

    if (found)
    {
        cout << "Defective coin found at index: " << defectiveIndex << endl;
        cout << "Defect Type: " << defectType << endl;
    }
    else
    {
        cout << "No defective coin found!" << endl;
    }

    return 0;
}
