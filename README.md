# K-Way Merge of Sorted Transaction Lists — Min-Heap vs. Pairwise Merging

## Problem

A financial system receives three already sorted transaction lists:

```
L1 = 10, 30, 50, 70
L2 = 20, 40, 60, 80
L3 = 15, 35, 55, 75
```

This repository:
- (a) merges them using a **min-heap based k-way merge**, tracing every heap state
- (b) merges them using **simple pairwise (sequential) merging**, tracing every comparison
- (c) analyses and compares heap size, comparison counts, time complexity, and
  space requirements, and recommends the better approach as k grows

## Repository contents

| File                     | Purpose                                                    |
|---------------------------|-------------------------------------------------------------|
| `heap_merge.c`             | C implementation of the min-heap k-way merge (Part a)       |
| `pairwise_merge.c`         | C implementation of simple pairwise merging (Part b)        |
| `input.txt`                | Input data used (the three sorted lists)                    |
| `output.txt`               | Captured console output of both programs when executed      |
| `trace_table.md`           | Step-by-step trace tables for both approaches                |
| `complexity_analysis.md`   | Time & space complexity derivation for both approaches      |
| `comparison_table.md`      | Side-by-side comparison (heap size, comparisons, complexity)|
| `conclusion.md`            | Justification of which approach is more suitable, and why   |

## Result

Both programs produce the same correct merged output:

```
10 15 20 30 35 40 50 55 60 70 75 80
```

## Summary of findings

| Metric                     | Min-Heap Merge   | Pairwise Merge |
|-------------------------------|--------------------|-------------------|
| Comparisons (k=3, N=12)         | 21                  | 18                 |
| Time complexity                  | O(N log k)          | O(N·k)             |
| Space complexity                 | O(k)                | O(N)               |

For this small k = 3 case the two are close, but the **min-heap approach
scales far better as the number of sorted lists (k) grows**, and is the
recommended approach for a real financial system that may ingest many
sorted transaction batches. See `conclusion.md` for the full justification.
