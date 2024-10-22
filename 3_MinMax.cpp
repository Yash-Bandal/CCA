#include <iostream>
#include <vector>
#include <utility>
using namespace std;

// Function to find the minimum and maximum using Divide and Conquer
pair<int, int> findMinMax(const vector<int>& arr, int low, int high) {
    // If there's only one element
    if (low == high) {
        return {arr[low], arr[low]};
    }
    
    // If there are two elements
    if (high == low + 1) {
        return {min(arr[low], arr[high]), max(arr[low], arr[high])};
    }

    // Find the mid index
    int mid = (low + high) / 2;

    // Recursively find min and max in both halves
    auto leftMinMax = findMinMax(arr, low, mid);
    auto rightMinMax = findMinMax(arr, mid + 1, high);

    // Combine results
    int overallMin = min(leftMinMax.first, rightMinMax.first);
    int overallMax = max(leftMinMax.second, rightMinMax.second);
    
    return {overallMin, overallMax};
}

int main() {
    vector<int> arr = {7, 9, 0, 5, 3, 4, 2, 1, 6};
    int n = arr.size();

    auto result = findMinMax(arr, 0, n - 1);
    cout << "Minimum Element: " << result.first << endl;
    cout << "Maximum Element: " << result.second << endl;

    return 0;
}
//or





#include <iostream>
#include <vector>
using namespace std;

// Function to find the minimum and maximum using Divide and Conquer
void findMinMax(const vector<int>& arr, int low, int high, int& min, int& max) {
    // Base case: If there's only one element
    if (low == high) {
        min = max = arr[low];
        return;
    }

    // Base case: If there are two elements
    if (high == low + 1) {
        if (arr[low] < arr[high]) {
            min = arr[low];
            max = arr[high];
        } else {
            min = arr[high];
            max = arr[low];
        }
        return;
    }

    // Recursive case
    int mid = (low + high) / 2;
    int min1, max1, min2, max2;

    // Find min and max in left half
    findMinMax(arr, low, mid, min1, max1);
    // Find min and max in right half
    findMinMax(arr, mid + 1, high, min2, max2);

    // Combine results
    min = (min1 < min2) ? min1 : min2;
    max = (max1 > max2) ? max1 : max2;
}

int main() {
    vector<int> arr = {7, 9, 0, 5, 3, 4, 2, 1, 6};
    int n = arr.size();
    int min, max;

    findMinMax(arr, 0, n - 1, min, max);

    cout << "Minimum Element: " << min << endl;
    cout << "Maximum Element: " << max << endl;

    return 0;
}
