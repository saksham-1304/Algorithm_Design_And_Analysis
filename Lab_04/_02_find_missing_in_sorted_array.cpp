#include<bits/stdc++.h>
using namespace std;

int findSmallestMissing(vector<int> &arr, int left, int right)
{
    if (left > right)
        return left;
    int mid = left + (right - left) / 2;
    if (arr[mid] == mid)
        return findSmallestMissing(arr, mid + 1, right);
    return findSmallestMissing(arr, left, mid - 1);
}

int main()
{
    vector<int> arr = {0, 1, 2, 3, 4, 6, 7, 8}; // Missing number = 5
    cout << "Smallest Missing Number: " << findSmallestMissing(arr, 0, arr.size() - 1) << endl;
    return 0;
}
