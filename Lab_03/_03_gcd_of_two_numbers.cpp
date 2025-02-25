#include <iostream>
using namespace std;

static int count = 0;
void method__Euclidean_Algo(int n, int m)
{
    count++;
    if (m == 0)
    {
        cout << "The GCD of given two numbers is " << n << endl;
        return;
    }

    method__Euclidean_Algo(m, n % m);
}
int main()
{
    int n, m;
    cout << "Enter first number:";
    cin >> n;
    cout << "Enter second number:";
    cin >> m;
    method__Euclidean_Algo(n, m);
    cout << "The recursion was called " << count << " times" << endl;
}