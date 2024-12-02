#include <iostream>
#include <vector>
#include <chrono>
#include <random>

class SortingComparison {
public:
    // insrtion sort
    void insertionSort(std::vector<int>& arr) {
        for (int i = 1; i < arr.size(); i++) {
            // take next index and set it equal to a temp
            int index = arr[i];
            int sortedSize = i - 1;

            // shift elements greater than index value
            while (arr[sortedSize] > index) {
                arr[sortedSize + 1] = arr[sortedSize];
                sortedSize--;
            }

            // move index in spot
            arr[sortedSize + 1] = index;
        }
    }

    // source I used to figure code out: https://www.youtube.com/watch?v=Hoixgm4-P4M
    // Helped function for my quicksort function
    int partition(std::vector<int>& arr, int low, int high) {
        int pivot = arr[low];
        int leftwall = low;
        int temp;

        for (int i = low + 1; i <= high; i++) {
            // if current less than pivot we want it on right
            if (arr[i] < pivot) {

                leftwall++;

                // swap logic
                temp = arr[leftwall];
                arr[leftwall] = arr[i];
                arr[i] = temp;

            }
        }

        temp = arr[low];
        arr[low] = arr[leftwall];
        arr[leftwall] = temp;

        return leftwall;
    }

    // quick sort
    void quickSort(std::vector<int>& arr, int left, int right) {
        if (left < right) {
            int pivot = partition(arr, left, right);
            quickSort(arr, left, pivot - 1);
            quickSort(arr, pivot + 1, right);
        }
    }

    void insert(std::vector<int> &a, int b) {
        a.push_back(b);
    }

    // remove first element of passes vecotr
    void remove(std::vector<int> &a) {
        a.erase(a.begin());
    }

    // Source for help planning function: https://www.youtube.com/watch?v=4VqmGXwpLqc&t=24s
    // take two arr's a & b and merge then into arr c
    std::vector<int> merge(std::vector<int> a, std::vector<int> b) {
        std::vector<int> c;

        // Empty vectors a or b
        while (!a.empty() && !b.empty()) {
            if (a[0] <= b[0]) {
                insert(c, b[0]);
                remove(a); // removes first element not whole array
            }
            else {
                insert(c, b[0]);
                remove(b);
            }
        }

        // Clearing residual elemetns
        while (!a.empty()) {
            insert(c, a[0]);
            remove(a);
        }

        while (!b.empty()) {
            insert(c, b[0]);
            remove(b);
        }

        return c;
    }

    // merge sort
    void mergeSort(std::vector<int>& arr, int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;

            mergeSort(arr, left, mid);
            mergeSort(arr, mid + 1, right); 

            std::vector<int> leftPart(arr.begin() + left, arr.begin() + mid + 1);
            std::vector<int> rightPart(arr.begin() + mid + 1, arr.begin() + right + 1);

            std::vector<int> merged = merge(leftPart, rightPart);

            for (int i = left; i <= right; i++) {
                arr[i] = merged[i - left];
            }
        }
    }

    // generate random integers
    std::vector<int> generateRandomArray(int size) {
        std::vector<int> arr(size);
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(1, 100000);
        for (int& x : arr) {
            x = dist(gen);
        }
        return arr;
    }

    // test sorted
    bool isSorted(const std::vector<int>& arr) {
        for (size_t i = 1; i < arr.size(); ++i) {
            if (arr[i] < arr[i - 1]) {
                return false;
            }
        }
        return true;
    }

    // comparison run time for three sorting algorithms
    void compareSortingAlgorithms() {
        std::vector<int> sizes = {1000, 10000, 100000}; // data scales
        for (int size : sizes) {
            std::vector<int> arr = generateRandomArray(size);
            
            std::cout << "Data size: " << size << "\n";

            // test insertion sort
            std::vector<int> arr_copy = arr;
            auto start = std::chrono::high_resolution_clock::now();
            insertionSort(arr_copy);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = end - start;
            std::cout << "Insertion Sort: " << elapsed.count() << " seconds\n";
            std::cout << "Sorted: " << (isSorted(arr_copy) ? "Yes" : "No") << "\n";

            // test quick sort
            arr_copy = arr;
            start = std::chrono::high_resolution_clock::now();
            quickSort(arr_copy, 0, arr_copy.size() - 1);
            end = std::chrono::high_resolution_clock::now();
            elapsed = end - start;
            std::cout << "Quick Sort: " << elapsed.count() << " seconds\n";
            std::cout << "Sorted: " << (isSorted(arr_copy) ? "Yes" : "No") << "\n";

            // test merge sort
            arr_copy = arr;
            start = std::chrono::high_resolution_clock::now();
            mergeSort(arr_copy, 0, arr_copy.size() - 1);
            end = std::chrono::high_resolution_clock::now();
            elapsed = end - start;
            std::cout << "Merge Sort: " << elapsed.count() << " seconds\n";
            std::cout << "Sorted: " << (isSorted(arr_copy) ? "Yes" : "No") << "\n\n";
        }
    }

private:
    // Some internal helper functions
};

int main() {
    SortingComparison sorter;
    sorter.compareSortingAlgorithms();
    return 0;
}
