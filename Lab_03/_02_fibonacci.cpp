#include <iostream>
using namespace std;
static int count = 0;
int fib(int n)
{
    count++;
    if (n == 1 || n == 0)
        return n;
    return fib(n - 1) + fib(n - 2);
}
int main()
{
    int n;
    cin >> n;
    cout << "The fibonacci number is " << fib(n) << endl;
    cout << "The recursion was called " << count << " times" << endl;
}