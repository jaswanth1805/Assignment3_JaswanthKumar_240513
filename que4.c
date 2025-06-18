#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH 10000
#define HASH_TABLE_SIZE 10007  // A prime number for better hashing

typedef struct Node {
    char* sorted_str;
    int* indices;
    int size;
    int capacity;
    struct Node* next;
} Node;

unsigned long hash(const char* str) {
    unsigned long hash = 5381;
    while (*str) {
        hash = ((hash << 5) + hash) + (*str);
        str++;
    }
    return hash % HASH_TABLE_SIZE;
}

char* sortString(const char* str) {
    int len = strlen(str);
    char* sorted = (char*)malloc((len + 1) * sizeof(char));
    strcpy(sorted, str);
    for (int i = 0; i < len - 1; ++i) {
        for (int j = i + 1; j < len; ++j) {
            if (sorted[i] > sorted[j]) {
                char temp = sorted[i];
                sorted[i] = sorted[j];
                sorted[j] = temp;
            }
        }
    }
    return sorted;
}

int** anagrams(const char** A, int n1, int* len1, int** len2) {
    Node* table[HASH_TABLE_SIZE] = {NULL};
    int group_count = 0;

    for (int i = 0; i < n1; i++) {
        char* sorted = sortString(A[i]);
        unsigned long h = hash(sorted);
        Node* curr = table[h];

        while (curr) {
            if (strcmp(curr->sorted_str, sorted) == 0) break;
            curr = curr->next;
        }

        if (curr == NULL) {
            Node* newNode = (Node*)malloc(sizeof(Node));
            newNode->sorted_str = sorted;
            newNode->size = 0;
            newNode->capacity = 2;
            newNode->indices = (int*)malloc(2 * sizeof(int));
            newNode->next = table[h];
            table[h] = newNode;
            curr = newNode;
            group_count++;
        } else {
            free(sorted); // we already have this sorted string
        }

        if (curr->size == curr->capacity) {
            curr->capacity *= 2;
            curr->indices = (int*)realloc(curr->indices, curr->capacity * sizeof(int));
        }
        curr->indices[curr->size++] = i + 1;
    }

    int** result = (int**)malloc(group_count * sizeof(int*));
    *len2 = (int*)malloc(group_count * sizeof(int));
    *len1 = group_count;

    int idx = 0;
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        Node* curr = table[i];
        while (curr) {
            result[idx] = curr->indices;
            (*len2)[idx] = curr->size;
            idx++;
            Node* temp = curr;
            curr = curr->next;
            free(temp->sorted_str);
            free(temp);  // Don't free temp->indices because it's used in result
        }
    }

    return result;
}
