#include <bits/stdc++.h>
#include<vector>
using namespace std;

int medianOfThree(vector<int> &arr, int low, int high)
{
    int mid = low + (high - low) / 2;

    if (arr[mid] < arr[low])
        swap(arr[mid], arr[low]);
    if (arr[high] < arr[low])
        swap(arr[high], arr[low]);
    if (arr[mid] < arr[high])
        swap(arr[mid], arr[high]);

    return arr[high];
}

int partition(vector<int> &arr, int low, int high)
{
    int pivot = medianOfThree(arr, low, high);
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (arr[j] <= pivot)
        {
            swap(arr[++i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<int> &arr, int low, int high)
{
    if (low < high)
    {
        int pivotIndex = partition(arr, low, high);
        quickSort(arr, low, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, high);
    }
}

int main()
{
    int n = 5000;
    vector<int> arr(n);

    srand(time(0));
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % 100000;
    }

    cout << "Sorting " << n << " random elements using QuickSort...\n";
    quickSort(arr, 0, n - 1);
    cout << "Sorting completed!\n";

    cout << "Sorted Array: ";
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}
