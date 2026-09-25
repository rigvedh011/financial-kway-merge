# Comparison: Min-Heap Merge vs. Pairwise Merge

| Criterion                                   | Min-Heap K-Way Merge            | Simple Pairwise Merge                |
|-----------------------------------------------|-----------------------------------|------------------------------------------|
| Auxiliary structure                            | Min-heap of size ≤ k              | Intermediate merged array(s)             |
| Max heap / structure size                      | k = 3                              | grows up to N = 12 (final intermediate list) |
| Number of comparisons (measured, k=3, n=4)     | 21                                  | 18                                        |
| Number of "passes" over the data               | 1 pass (N extract-min ops)         | k − 1 = 2 passes                          |
| Time complexity (general k, n)                  | **O(N log k)**                      | **O(N·k)**                                 |
| Space complexity                                | **O(k)** extra                      | **O(N)** extra                             |
| Behaviour as k increases (n fixed)              | grows as **log k** — very slow growth | grows **linearly with k** — much faster growth |
| Data movement per element                       | O(log k) (one sift per extraction) | O(k) (touched again at every later pass)   |
| Ease of implementation                          | Needs a heap data structure         | Simple, uses only array merge logic        |
| Suitability for external/multi-file merging     | Excellent — natural fit             | Poor — repeated full passes over growing data |

## When the number of sorted lists (k) increases

- The heap approach's cost grows as **O(N log k)** — for k = 3 → log₂3 ≈ 1.58,
  for k = 100 → log₂100 ≈ 6.64. Even a 33× increase in k barely more than
  quadruples the log factor.
- The pairwise approach's cost grows as **O(N·k)** — directly proportional
  to k. Going from k = 3 to k = 100 multiplies the work by roughly 33×.
- Pairwise merging also repeatedly re-copies already-merged data into
  larger and larger intermediate arrays (the classic "merge one file at a
  time" pattern used in external sorting before heaps were adopted),
  which is exactly why real database/external-sort systems use a
  min-heap ("tournament tree" / "replacement selection") once the number
  of runs to merge grows large.

**Conclusion of the comparison:** for a small, fixed k (like 3 here) the
two approaches are close in comparison count, but the **min-heap approach
scales far better** and is the standard choice whenever k — the number of
sorted lists/files being merged — is large or grows over time.
