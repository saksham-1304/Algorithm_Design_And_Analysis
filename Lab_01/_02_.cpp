#include <bits/stdc++.h>

using namespace std;
void method1(int n, int m)
{
    for (int i = min(n, m); i >= 1; i--)
    {
        if (n % i == 0 && m % i == 0)
        {
            cout << "The GCD of given two numbers is " << i << endl;
            break;
        }
    }
}

void method2__Euclidean_Algo(int n, int m)
{
    if (m == 0)
    {
        cout << "The GCD of given two numbers is " << n << endl;
        return;
    }

    method2__Euclidean_Algo(m, n % m);
}
int main()
{
    int n, m;
    cout << "Enter first number:";
    cin >> n;
    cout << "Enter second number:";
    cin >> m;
    method1(n, m);
    method2__Euclidean_Algo(n, m);
}