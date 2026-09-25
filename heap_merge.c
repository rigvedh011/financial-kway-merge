/* ============================================================
   Q: K-way merge of k sorted lists using a Min-Heap
   File: heap_merge.c
   ------------------------------------------------------------
   Each heap node stores:
        value        -> the element value
        listIndex    -> which input list (0..k-1) it came from
        elemIndex    -> position within that list
   The heap is a MIN-HEAP ordered on 'value', implemented as an
   array (standard binary-heap representation).

   Every heapify-up / heapify-down step, and every heap state
   after a pop+push cycle, is printed so a trace table can be
   built directly from the program's own output.

   Counters kept:
        comparisons  -> key comparisons made while sifting the
                         heap up/down (the dominant operation)
        heapOps      -> number of insert/extract-min operations
   ============================================================ */

#include <stdio.h>
#include <stdlib.h>

#define MAX_LISTS  10
#define MAX_LEN    100

typedef struct {
    int value;
    int listIndex;
    int elemIndex;
} HeapNode;

HeapNode heap[MAX_LISTS];
int heapSize = 0;

long comparisons = 0;   /* count of value comparisons during sift operations   */
long heapOps     = 0;   /* count of insert / extract-min operations            */

void printHeap(const char *label) {
    printf("%-28s [ ", label);
    for (int i = 0; i < heapSize; i++) {
        printf("%d(L%d)", heap[i].value, heap[i].listIndex + 1);
        if (i != heapSize - 1) printf(", ");
    }
    printf(" ]  (heap size = %d)\n", heapSize);
}

void swapNode(HeapNode *a, HeapNode *b) {
    HeapNode t = *a;
    *a = *b;
    *b = t;
}

/* Move node at index i UP until heap property restored */
void siftUp(int i) {
    while (i > 0) {
        int parent = (i - 1) / 2;
        comparisons++;
        if (heap[i].value < heap[parent].value) {
            swapNode(&heap[i], &heap[parent]);
            i = parent;
        } else {
            break;
        }
    }
}

/* Move node at index i DOWN until heap property restored */
void siftDown(int i) {
    while (1) {
        int left  = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;

        if (left < heapSize) {
            comparisons++;
            if (heap[left].value < heap[smallest].value)
                smallest = left;
        }
        if (right < heapSize) {
            comparisons++;
            if (heap[right].value < heap[smallest].value)
                smallest = right;
        }
        if (smallest != i) {
            swapNode(&heap[i], &heap[smallest]);
            i = smallest;
        } else {
            break;
        }
    }
}

void heapInsert(HeapNode node) {
    heap[heapSize] = node;
    heapSize++;
    heapOps++;
    siftUp(heapSize - 1);
}

HeapNode heapExtractMin(void) {
    HeapNode root = heap[0];
    heapSize--;
    heap[0] = heap[heapSize];
    heapOps++;
    if (heapSize > 0) siftDown(0);
    return root;
}

int main(void) {
    /* -------- input data (as given in the assignment) -------- */
    int L1[] = {10, 30, 50, 70};
    int L2[] = {20, 40, 60, 80};
    int L3[] = {15, 35, 55, 75};

    int *lists[MAX_LISTS];
    int  lenOf[MAX_LISTS];
    int  k = 3;

    lists[0] = L1; lenOf[0] = 4;
    lists[1] = L2; lenOf[1] = 4;
    lists[2] = L3; lenOf[2] = 4;

    int result[MAX_LEN];
    int resCount = 0;

    printf("================= K-WAY MERGE USING MIN-HEAP =================\n\n");
    printf("Input lists:\n");
    for (int i = 0; i < k; i++) {
        printf(" L%d = [ ", i + 1);
        for (int j = 0; j < lenOf[i]; j++) printf("%d ", lists[i][j]);
        printf("]\n");
    }
    printf("\n--- STEP 1: Build initial heap with first element of each list ---\n");

    for (int i = 0; i < k; i++) {
        HeapNode n = { lists[i][0], i, 0 };
        heapInsert(n);
        char label[40];
        snprintf(label, sizeof(label), "Insert %d from L%d ->", lists[i][0], i + 1);
        printHeap(label);
    }

    printf("\n--- STEP 2: Repeatedly extract-min, output it, push next from same list ---\n");

    int iteration = 1;
    while (heapSize > 0) {
        HeapNode minNode = heapExtractMin();
        result[resCount++] = minNode.value;

        char label[60];
        snprintf(label, sizeof(label), "[%2d] Extract %d (from L%d) ->",
                  iteration, minNode.value, minNode.listIndex + 1);
        printHeap(label);

        int li = minNode.listIndex;
        int ei = minNode.elemIndex + 1;
        if (ei < lenOf[li]) {
            HeapNode n = { lists[li][ei], li, ei };
            heapInsert(n);
            char label2[60];
            snprintf(label2, sizeof(label2), "      Insert %d from L%d  ->",
                      lists[li][ei], li + 1);
            printHeap(label2);
        }
        iteration++;
    }

    printf("\n--- RESULT ---\n");
    printf("Merged sorted output: [ ");
    for (int i = 0; i < resCount; i++) printf("%d ", result[i]);
    printf("]\n");

    printf("\n--- OPERATION COUNTS (Min-Heap approach) ---\n");
    printf("Total elements merged      : %d\n", resCount);
    printf("Total heap operations      : %ld  (inserts + extract-mins)\n", heapOps);
    printf("Total key comparisons      : %ld  (during sift-up / sift-down)\n", comparisons);
    printf("Max heap size reached      : %d\n", k);

    return 0;
}
