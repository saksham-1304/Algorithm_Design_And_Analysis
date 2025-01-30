// Tower Of Hanoi

#include <iostream>
using namespace std;

// Function to perform the Tower of Hanoi
static int count = 0;
void towerOfHanoi(int n, char source, char destination, char aux_rod)
{
    count++;
    if (n == 1)
    {
        cout << "Move disk 1 from rod " << source << " to rod " << destination << endl;
        return;
    }
    towerOfHanoi(n - 1, source, aux_rod, destination);
    cout << "Move disk " << n << " from rod " << source << " to rod " << destination << endl;
    towerOfHanoi(n - 1, aux_rod, destination, source);
}

int main()
{
    int n; // Number of disks
    cout << "Enter number of discs: ";
    cin >> n;
    towerOfHanoi(n, 'A', 'C', 'B'); // A, B, and C are the rods
    cout << "The recursion was called " << count << " times" << endl;

    return 0;
}
