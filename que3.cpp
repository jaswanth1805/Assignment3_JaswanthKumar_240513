#include <stdlib.h>
#include <limits.h>

int* twoSum(const int* A, int n1, int B, int *len1) {
    int* result = (int*)malloc(2 * sizeof(int));
    int min_index1 = INT_MAX, min_index2 = INT_MAX;

    for (int i = 0; i < n1; i++) {
        for (int j = i + 1; j < n1; j++) {
            if (A[i] + A[j] == B) {
                if (j + 1 < min_index2 || (j + 1 == min_index2 && i + 1 < min_index1)) {
                    min_index1 = i + 1;
                    min_index2 = j + 1;
                }
            }
        }
    }

    if (min_index1 != INT_MAX) {
        result[0] = min_index1;
        result[1] = min_index2;
        *len1 = 2;
        return result;
    } else {
        *len1 = 0;
        return NULL;
    }
}
