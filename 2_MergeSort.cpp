#include <bits/stdc++.h>
using namespace std;

void merge(vector<int> &arr, int low, int mid, int high) {
    vector<int> temp;
    int left = low, right = mid + 1;
    while (left <= mid && right <= high) {
        if (arr[left] < arr[right]) {
            temp.push_back(arr[left]);
            left++;
        } else {
            temp.push_back(arr[right]);
            right++;
        }
    }
    while (left <= mid) temp.push_back(arr[left++]);
    while (right <= high) temp.push_back(arr[right++]);
    for (int i = low; i <= high; i++) {
        arr[i] = temp[i - low];
    }
}

void mergeSort(vector<int> &arr, int low, int high) {
    if (low < high) {
        int mid = (low + high) / 2;
        mergeSort(arr, low, mid);
        mergeSort(arr, mid + 1, high);
        merge(arr, low, mid, high);
    }
}


void printArray(const vector<int> &arr, int n) {
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    vector<int> arr = {7, 9, 0, 5, 3, 4, 2, 1, 6};
    int n = arr.size();
    
    cout << "Before Sort :" << endl;
    printArray(arr,n);
    
    mergeSort(arr, 0, n - 1);
    
    cout << "After Sorting :" << endl;
    printArray(arr, n);
    
    return 0;
}
