#include <stdio.h>
#include <stdlib.h>

// A simple min-heap implementation
#define MAX 100000

long long heap[MAX+1];
int heapSize = 0;

// Swap helper
void swap(int i, int j) {
    long long temp = heap[i];
    heap[i] = heap[j];
    heap[j] = temp;
}

// Insert into min-heap
void insert(long long val) {
    heap[++heapSize] = val;
    int i = heapSize;

    // Bubble up
    while (i > 1 && heap[i] < heap[i/2]) {
        swap(i, i/2);
        i /= 2;
    }
}

// Heapify down
void heapify(int i) {
    int left = 2*i, right = 2*i+1, smallest = i;

    if (left <= heapSize && heap[left] < heap[smallest]) smallest = left;
    if (right <= heapSize && heap[right] < heap[smallest]) smallest = right;

    if (smallest != i) {
        swap(i, smallest);
        heapify(smallest);
    }
}

// Delete specific value
void deleteVal(long long val) {
    int i;
    for (i = 1; i <= heapSize; i++) {
        if (heap[i] == val) break;
    }

    if (i <= heapSize) {
        heap[i] = heap[heapSize--]; // Replace with last element
        // Fix heap
        if (i > 1 && heap[i] < heap[i/2]) {
            // Bubble up
            while (i > 1 && heap[i] < heap[i/2]) {
                swap(i, i/2);
                i /= 2;
            }
        } else {
            heapify(i);
        }
    }
}

// Get minimum (root of heap)
long long getMin() {
    return heap[1];
}

int main() {
    int Q;
    scanf("%d", &Q);

    for (int i = 0; i < Q; i++) {
        int type;
        long long val;
        scanf("%d", &type);

        if (type == 1) {
            scanf("%lld", &val);
            insert(val);
        } else if (type == 2) {
            scanf("%lld", &val);
            deleteVal(val);
        } else if (type == 3) {
            printf("%lld\n", getMin());
        }
    }

    return 0;
}
