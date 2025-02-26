// Merge Sort

#include <iostream>
using namespace std;

const int MAX_SIZE = 1000; // Maximum size of the link array

struct Node
{
    int value;
    int next;
};

Node linkArray[MAX_SIZE]; // Array to store values and links
int head = -1, freeIndex = 0;

// Function to insert elements into the link array
void insert(int val)
{
    if (freeIndex >= MAX_SIZE)
    {
        cout << "Link array full!" << endl;
        return;
    }
    linkArray[freeIndex].value = val;
    linkArray[freeIndex].next = (head == -1) ? -1 : head;
    head = freeIndex++;
}

// Function to split linked array into two halves
void split(int start, int &left, int &right)
{
    if (start == -1 || linkArray[start].next == -1)
    {
        left = start;
        right = -1;
        return;
    }
    int slow = start, fast = linkArray[start].next;
    while (fast != -1 && linkArray[fast].next != -1)
    {
        slow = linkArray[slow].next;
        fast = linkArray[linkArray[fast].next].next;
    }
    left = start;
    right = linkArray[slow].next;
    linkArray[slow].next = -1;
}

// Function to merge two sorted lists
int merge(int left, int right)
{
    if (left == -1)
        return right;
    if (right == -1)
        return left;

    int result;
    if (linkArray[left].value <= linkArray[right].value)
    {
        result = left;
        linkArray[left].next = merge(linkArray[left].next, right);
    }
    else
    {
        result = right;
        linkArray[right].next = merge(left, linkArray[right].next);
    }
    return result;
}

// Merge Sort function
int mergeSort(int start)
{
    if (start == -1 || linkArray[start].next == -1)
        return start;
    int left, right;
    split(start, left, right);
    left = mergeSort(left);
    right = mergeSort(right);
    return merge(left, right);
}

// Function to display sorted link array
void display(int start)
{
    while (start != -1)
    {
        cout << linkArray[start].value << " ";
        start = linkArray[start].next;
    }
    cout << endl;
}

int main()
{
    // Insert values into the linked array
    insert(30);
    insert(10);
    insert(50);
    insert(20);
    insert(40);

    cout << "Original List: ";
    display(head);

    head = mergeSort(head); // Sort using Merge Sort

    cout << "Sorted List: ";
    display(head);

    return 0;
}
