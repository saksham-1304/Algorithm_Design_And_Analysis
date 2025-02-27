#include <iostream>
using namespace std;
int n;
int findDefective(int arr[], int l, int r)
{
    cout << l << " " << r << endl;
    if (r - l == 1)
    {
        if (arr[l] == arr[r])
            return -1;
        int x = (l != 0 && r != 0) ? 0 : ((l != 1 && r != 1) ? 1 : 2);
        if (arr[x] == arr[r])
            return arr[l];
        return arr[r];
    }
    if (l > r)
        return -1;
    if (l == r)
    {
        return arr[l];
    }
    int n = r - l + 1;
    int sum1 = 0, sum2 = 0;
    for (int i = 0; i < n / 3; i++)
    {
        sum1 += arr[l + i];
        sum2 += arr[r - i];
    }
    if (sum1 == sum2)
        return findDefective(arr, l + n / 3, r - n / 3);
    int val1 = findDefective(arr, l, l + n / 3);
    if (val1 != -1)
    {
        return val1;
    }
    return findDefective(arr, r - n / 3 + 1, r);
}
int main()
{
    cin >> n;
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    int ans = findDefective(arr, 0, n - 1);
    cout << ans << endl;
}
