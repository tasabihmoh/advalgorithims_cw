#include <iostream>

using namespace std;

void removeDuplicates(char arr[], int& n) {
    const int CHAR_RANGE = 256;
    bool hashTable[CHAR_RANGE] = {false};
    int index = 0;
    for (int i = 0; i < n; ++i) {
        if (!hashTable[arr[i]]) {
            hashTable[arr[i]] = true;
            arr[index++] = arr[i];
        }
    }
    n = index;
}

int main() {
    char arr[] = {'a', 'b', 'c', 'a', 'd', 'b', 'e', 'c'};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Original array: ";
    for (int i = 0; i < n; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;

    removeDuplicates(arr, n);

    cout << "Array after removing duplicates: ";
    for (int i = 0; i < n; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}
