#include <iostream>
#include <vector>
using namespace std;

void subsetSum(vector<int> &nums, int target, int index, vector<int> &path, int total)
{
    if (total == target)
    {
        cout << "{ ";
        for (int num : path)
            cout << num << " ";
        cout << "}" << endl;
        return;
    }
    if (total > target || index == nums.size())
        return;

    // Include current element
    path.push_back(nums[index]);
    subsetSum(nums, target, index + 1, path, total + nums[index]);

    // Exclude current element
    path.pop_back();
    subsetSum(nums, target, index + 1, path, total);
}

int main()
{
    int n, target;
    cout << "Enter number of elements: ";
    cin >> n;
    vector<int> nums(n);
    cout << "Enter elements: ";
    for (int i = 0; i < n; i++)
        cin >> nums[i];
    cout << "Enter target sum: ";
    cin >> target;

    vector<int> path;
    cout << "Subsets with sum " << target << ":" << endl;
    subsetSum(nums, target, 0, path, 0);
    return 0;
}

/*
Test Case:
Enter number of elements: 5
Enter elements: 2 4 6 8 10
Enter target sum: 14
Subsets with sum 14:
{ 2 4 8 }
{ 4 10 }
{ 6 8 }
*/
