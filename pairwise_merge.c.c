/* ============================================================
   Q: Pairwise merging of k sorted lists (simple / sequential)
   File: pairwise_merge.c
   ------------------------------------------------------------
   Strategy: merge L1 & L2 first (standard 2-way merge of
   sorted arrays) to get M1, then merge M1 & L3 to get the
   final result. This is the "merge one at a time" approach
   most students implement first, before learning the heap
   method.

   Each 2-way merge step is traced, and every comparison
   between two elements is counted.
   ============================================================ */

#include <stdio.h>

#define MAX_LEN 200

long comparisons = 0;

/* Merge two sorted arrays a[0..na-1] and b[0..nb-1] into out[]
   Returns length of merged array. Prints a step-by-step trace. */
int mergeTwo(int a[], int na, int b[], int nb, int out[], const char *labelA, const char *labelB) {
    int i = 0, j = 0, k = 0;
    printf("\nMerging %s and %s:\n", labelA, labelB);
    while (i < na && j < nb) {
        comparisons++;
        printf("  compare %s[%d]=%d vs %s[%d]=%d -> ",
               labelA, i, a[i], labelB, j, b[j]);
        if (a[i] <= b[j]) {
            out[k++] = a[i];
            printf("take %d from %s\n", a[i], labelA);
            i++;
        } else {
            out[k++] = b[j];
            printf("take %d from %s\n", b[j], labelB);
            j++;
        }
    }
    while (i < na) { printf("  remaining: take %d from %s\n", a[i], labelA); out[k++] = a[i++]; }
    while (j < nb) { printf("  remaining: take %d from %s\n", b[j], labelB); out[k++] = b[j++]; }

    printf("  Result so far: [ ");
    for (int x = 0; x < k; x++) printf("%d ", out[x]);
    printf("]\n");

    return k;
}

int main(void) {
    int L1[] = {10, 30, 50, 70};
    int L2[] = {20, 40, 60, 80};
    int L3[] = {15, 35, 55, 75};
    int n1 = 4, n2 = 4, n3 = 4;

    int M1[MAX_LEN];   /* result of L1 + L2 */
    int Final[MAX_LEN]; /* result of M1 + L3 */

    printf("================ PAIRWISE MERGING (SIMPLE) ================\n");
    printf("\nInput lists:\n L1 = [ 10 30 50 70 ]\n L2 = [ 20 40 60 80 ]\n L3 = [ 15 35 55 75 ]\n");

    printf("\n--- PASS 1: merge L1 and L2 ---");
    int m1len = mergeTwo(L1, n1, L2, n2, M1, "L1", "L2");

    printf("\n--- PASS 2: merge M1 (=L1+L2) and L3 ---");
    int flen = mergeTwo(M1, m1len, L3, n3, Final, "M1", "L3");

    printf("\n--- RESULT ---\n");
    printf("Merged sorted output: [ ");
    for (int i = 0; i < flen; i++) printf("%d ", Final[i]);
    printf("]\n");

    printf("\n--- OPERATION COUNTS (Pairwise approach) ---\n");
    printf("Total elements merged      : %d\n", flen);
    printf("Number of merge passes     : 2   (k-1 passes for k lists)\n");
    printf("Total key comparisons      : %ld\n", comparisons);

    return 0;
}
