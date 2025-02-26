// Selection Sort

#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

// Selection Sort Implementation
void selectionSort(vector<int> &arr)
{
    int n = arr.size();
    for (int i = 0; i < n - 1; i++)
    {
        int min_index = i;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[min_index])
            {
                min_index = j;
            }
        }
        swap(arr[i], arr[min_index]);
    }
}

int main()
{
    srand(time(0)); // Seed for random number generation

    vector<int> test_sizes = {100, 500, 1000, 2000, 3000, 4000, 5000}; // Different values of n

    for (int n : test_sizes)
    {
        vector<int> arr(n);
        for (int i = 0; i < n; i++)
        {
            arr[i] = rand() % 10000; // Generate random numbers
        }

        auto start = high_resolution_clock::now(); // Start time
        selectionSort(arr);
        auto end = high_resolution_clock::now(); // End time

        double time_taken = duration<double, milli>(end - start).count(); // Convert to milliseconds
        cout << "n = " << n << ", Time taken = " << time_taken << " ms" << endl;
    }

    return 0;
}
