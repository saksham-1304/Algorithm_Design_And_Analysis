#include <bits/stdc++.h>
using namespace std;

// Insertion Sort function (for small subarrays)
void insertionSort(vector<int> &arr, int low, int high)
{
    for (int i = low + 1; i <= high; i++)
    {
        int key = arr[i];
        int j = i - 1;
        while (j >= low && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Function to partition the array using a random pivot
int partition(vector<int> &arr, int low, int high)
{
    int randomPivot = low + rand() % (high - low + 1);
    swap(arr[randomPivot], arr[high]); // Move random pivot to end

    int pivot = arr[high];
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

// Hybrid QuickSort function (uses Insertion Sort for small partitions)
void hybridQuickSort(vector<int> &arr, int low, int high)
{
    if (high - low + 1 <= 4)
    { // If partition size is <= 4, use Insertion Sort
        insertionSort(arr, low, high);
        return;
    }

    if (low < high)
    {
        int pivotIndex = partition(arr, low, high);
        hybridQuickSort(arr, low, pivotIndex - 1);
        hybridQuickSort(arr, pivotIndex + 1, high);
    }
}

// Function to print the array
void printArray(const vector<int> &arr)
{
    for (int num : arr)
    {
        cout << num << " ";
    }
    cout << endl;
}

int main()
{
    srand(time(0)); // Seed for random pivot selection

    int n;
    cout << "Enter the number of elements: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter " << n << " elements:\n";
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    cout << "Original array: ";
    printArray(arr);

    hybridQuickSort(arr, 0, n - 1);

    cout << "Sorted array: ";
    printArray(arr);

    return 0;
}
