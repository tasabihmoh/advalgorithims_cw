#include <iostream>
#include <vector>

using namespace std;

// Function to swap two integers
void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// Function to partition the array based on the pivot value
int partition(vector<int>& arr, int low, int high, int k) {
    if (low >= high)
        return low;

    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= k) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Recursive function to rearrange the array based on the pivot value
void rearrange(vector<int>& arr, int low, int high, int k) {
    if (low < high) {
        int pi = partition(arr, low, high, k);
        rearrange(arr, low, pi - 1, k);
        rearrange(arr, pi + 1, high, k);
    }
}

// Function to rearrange the array based on the pivot value k
void rearrangeArray(vector<int>& arr, int k) {
    rearrange(arr, 0, arr.size() - 1, k);
}

int main() {
    // Input array and pivot value
    vector<int> arr = { 3, 1, 12, 9, 4, 10, 54, 34, 12, 89 };
    int k = 12;

    // Printing unsorted array
    cout << "Unsorted Array: [";
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i];
        if (i != arr.size() - 1)
            cout << ", ";
    }
    cout << "]" << endl;

    // Printing pivot value
    cout << "Pivot Value: " << k << endl;

    // Rearranging the array
    rearrangeArray(arr, k);

    // Printing rearranged array
    cout << "Output: [";
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i];
        if (i != arr.size() - 1)
            cout << ", ";
    }
    cout << "]" << endl;

    return 0;
}
