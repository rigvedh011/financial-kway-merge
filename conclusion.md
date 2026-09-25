# Conclusion

Both approaches correctly merge the three sorted transaction lists
L1 = {10, 30, 50, 70}, L2 = {20, 40, 60, 80}, L3 = {15, 35, 55, 75}
into the sorted sequence:

**10, 15, 20, 30, 35, 40, 50, 55, 60, 70, 75, 80**

## Execution results (k = 3, n = 4, N = 12)

| Approach     | Comparisons | Time complexity | Space complexity | Heap/structure size |
|--------------|-------------|------------------|---------------------|------------------------|
| Min-Heap     | 21          | O(N log k)       | O(k)                 | 3                       |
| Pairwise     | 18          | O(N·k)           | O(N)                 | grows to 12             |

## Justification

For this specific input (only k = 3 small lists), the pairwise approach
happens to use slightly fewer raw comparisons, and is simpler to code.
However, this is only because k is small — with k = 3, `log₂k ≈ 1.58` is
already close to k itself, so the asymptotic advantage of the heap
(`O(log k)` per element vs. `O(k)` per element) has little room to show.

**In a financial system that may need to merge many more transaction
files (k growing — multiple bank branches, multiple days' batch files,
etc.), the min-heap approach is the more suitable and scalable design:**

- Its per-element cost grows only as **O(log k)**, so doubling or even
  10×-ing the number of source lists barely increases the work per
  element.
- It uses only **O(k)** auxiliary space (the heap), rather than
  materialising ever-larger intermediate merged arrays as pairwise
  merging does.
- It processes each input element exactly once through the heap
  (a single O(log k) sift), instead of re-touching earlier-merged
  elements at every subsequent pairwise pass.

**Final recommendation:** use the simple pairwise merge only when the
number of lists k is small and fixed (as a quick, easy-to-implement
solution). Use the min-heap k-way merge whenever k can be large or grows
over time — which is the realistic case for a financial transaction
system that ingests sorted batches from many sources. This is also why
production external-merge-sort and multi-way-merge systems (databases,
big-data pipelines) universally use the min-heap / tournament-tree
technique rather than sequential pairwise merging.
