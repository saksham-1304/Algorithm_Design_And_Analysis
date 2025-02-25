// Merge Sort

#include <bits/stdc++.h>
using namespace std;
using namespace chrono;

void merge(vector<int> &arr, int left, int mid, int right)
{
    int n1 = mid - left + 1, n2 = right - mid;
    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int i = 0; i < n2; i++)
        R[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
        arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i < n1)
        arr[k++] = L[i++];
    while (j < n2)
        arr[k++] = R[j++];
}

void mergeSort(vector<int> &arr, int left, int right)
{
    if (left >= right)
        return;
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

int main()
{
    vector<int> sizes = {5000, 10000, 20000, 50000, 100000};
    vector<double> times;

    for (int n : sizes)
    {
        vector<int> arr(n);
        for (int i = 0; i < n; i++)
            arr[i] = rand() % 100000;

        auto start = high_resolution_clock::now();
        mergeSort(arr, 0, n - 1);
        auto end = high_resolution_clock::now();

        double duration = duration_cast<microseconds>(end - start).count() / 1e6;
        times.push_back(duration);
        cout << "Size: " << n << " | Time: " << duration << " sec" << endl;
    }

    return 0;
}
