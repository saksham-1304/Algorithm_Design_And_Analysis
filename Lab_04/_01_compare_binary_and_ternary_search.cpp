// Binary V/s Ternary Search

#include <bits/stdc++.h>
using namespace std;
int binarySearch(const vector<int> &arr, int left, int right, int key, int &comparisons)
{
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        comparisons++;
        if (arr[mid] == key)
            return mid;
        else if (arr[mid] < key)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

int ternarySearch(const vector<int> &arr, int left, int right, int key, int &comparisons)
{
    while (left <= right)
    {
        int mid1 = left + (right - left) / 3;
        int mid2 = right - (right - left) / 3;
        comparisons++;
        if (arr[mid1] == key)
            return mid1;
        comparisons++;
        if (arr[mid2] == key)
            return mid2;
        if (key < arr[mid1])
            right = mid1 - 1;
        else if (key > arr[mid2])
            left = mid2 + 1;
        else
        {
            left = mid1 + 1;
            right = mid2 - 1;
        }
    }
    return -1;
}

void runExperiment(int n)
{
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        arr[i] = i;

    int key = n - 1;
    int binComparisons = 0, terComparisons = 0;

    binarySearch(arr, 0, n - 1, key, binComparisons);
    ternarySearch(arr, 0, n - 1, key, terComparisons);

    cout << "Size: " << n << " | Binary Comparisons: " << binComparisons << " | Ternary Comparisons: " << terComparisons << endl;
}

int main()
{
    vector<int> sizes = {100, 500, 1000, 5000, 10000, 50000};
    vector<int> binComp, terComp;

    for (int n : sizes)
    {
        int binComparisons = 0, terComparisons = 0;
        runExperiment(n);
    }

    return 0;
}
