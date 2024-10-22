#include <iostream>
#include <vector>
using namespace std;

int makePartition(vector<int> &arr, int low, int high) {
    int pivot = arr[low], i = low, j = high;
    while (i < j) {
        while (arr[i] <= pivot && i <= high - 1) i++;
        while (arr[j] > pivot && j >= low + 1) j--;
        if (i < j) swap(arr[i], arr[j]);
    }
    swap(arr[j], arr[low]);
    return j;
}

void quickSort(vector<int> &arr, int low, int high) {
    if (low < high) {
        int partInd = makePartition(arr, low, high);
        quickSort(arr, low, partInd - 1);
        quickSort(arr, partInd + 1, high);
    }
}

void printArray(const vector<int> &arr) {
    for (int num : arr) cout << num << " ";
    cout << endl;
}

int main() {
    vector<int> arr = {7, 9, 0, 5, 3, 4, 2, 1, 6};
    cout << "Before QuickSort :" << endl;
    printArray(arr);
    quickSort(arr, 0, arr.size() - 1);
    cout << "After Sorting :" << endl;
    printArray(arr);
    return 0;
}
