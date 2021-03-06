#include <iostream>
#include <ctime>
#include <omp.h>

using namespace std;

void printArray(int* input, int length) {
    cout << "{";
    for (unsigned int i = 0; i < length; i++) {
        cout << input[i];

        if (i < length - 1) {
            cout << ", ";
        }
    }
    cout << "}" << endl;
}

int* randomArray(unsigned int length, int minNumber, int maxNumber) {
    int* output = new int[length];

    for (unsigned int i = 0; i < length; i++) {
        output[i] = minNumber + (rand() % (maxNumber - minNumber));
    }

    return output;
}

void quicksort(int* input, int startIndex, int endIndex) {
    if(endIndex - startIndex > 0) {
        int pivot = input[(startIndex + endIndex)/2];
        int i = startIndex;
        int j = endIndex;

        while(i <= j) {
            while (input[i] < pivot) {
                i++;
            }

            while (input[j] > pivot) {
                j--;
            }

            if(i <= j) {
                swap(input[i], input[j]);
                i++; j--;
            }
        }

        if(j > startIndex) {
            quicksort(input, startIndex, j);
        }

        if(i < endIndex) {
            quicksort(input, i, endIndex);
        }
    }
}

int main() {
    srand(time(NULL));

    const int arrayLength = 1000000000;
    const bool print = false;
    int* array = randomArray(arrayLength, 1, 1000);

    if(print)
        cout << "Input: ", printArray(array, arrayLength);

    auto start = omp_get_wtime();
    quicksort(array, 0, arrayLength-1);
    auto end = omp_get_wtime();

    if(print)
        cout << "Output: ", printArray(array, arrayLength);

    cout << "Time: " << end - start << "s" << endl;

    delete array;
    return 0;
}
