#include <iostream>
using namespace std;
#define MAX_SIZE 100 // Maximum size of the link array

// Global arrays to represent Link List
int data[MAX_SIZE]; // Stores actual values
int link[MAX_SIZE]; // Stores indices of the next elements
int start;          // Head of the linked list

// Function to print the sorted linked array
void printList(int start)
{
    int index = start;
    while (index != -1)
    {
        cout << data[index] << " ";
        index = link[index];
    }
    cout << endl;
}

// Function to find the middle of the linked array list
int findMiddle(int start)
{
    if (start == -1)
        return -1;
    int slow = start, fast = start;
    int prev = -1;

    while (fast != -1 && link[fast] != -1)
    {
        prev = slow;
        slow = link[slow];
        fast = link[link[fast]];
    }

    if (prev != -1)
        link[prev] = -1; // Break the list into two halves
    return slow;
}

// Merge two sorted linked lists
int merge(int left, int right)
{
    if (left == -1)
        return right;
    if (right == -1)
        return left;

    int head;
    if (data[left] <= data[right])
    {
        head = left;
        left = link[left];
    }
    else
    {
        head = right;
        right = link[right];
    }

    int tail = head;
    while (left != -1 && right != -1)
    {
        if (data[left] <= data[right])
        {
            link[tail] = left;
            tail = left;
            left = link[left];
        }
        else
        {
            link[tail] = right;
            tail = right;
            right = link[right];
        }
    }

    if (left != -1)
        link[tail] = left;
    else
        link[tail] = right;

    return head;
}

// Merge Sort using linked array representation
int mergeSort(int start)
{
    if (start == -1 || link[start] == -1)
        return start; // Base case (1 or 0 elements)

    int mid = findMiddle(start); // Find midpoint and split the list
    int left = mergeSort(start); // Sort left half
    int right = mergeSort(mid);  // Sort right half

    return merge(left, right); // Merge two sorted halves
}

int main()
{
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    cout << "Enter the elements: ";
    for (int i = 0; i < n; i++)
    {
        cin >> data[i];
        link[i] = i + 1;
    }
    link[n - 1] = -1; // End of list
    start = 0;        // Start at the first element

    cout << "Original List: ";
    printList(start);

    start = mergeSort(start);

    cout << "Sorted List: ";
    printList(start);

    return 0;
}
