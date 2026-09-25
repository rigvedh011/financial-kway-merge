# Complexity Analysis

Let:
- **k** = number of sorted lists (here k = 3)
- **n** = size of each list (here n = 4, assume roughly equal-sized lists)
- **N** = total number of elements = k·n (here N = 12)

---

## (a) Min-Heap K-Way Merge

**How it works:** maintain a min-heap of at most k elements (the current
"front" element of each list). Repeatedly extract the minimum, output it,
then insert the next element from the same list the minimum came from.

- Building the initial heap: k insertions, each O(log k) → **O(k log k)**
- Main loop: N extract-min / insert operations total, each costs O(log k)
  (sift-down or sift-up over a heap of size ≤ k)
  → **O(N log k)**
- **Total time complexity: O(N log k)**
- **Space complexity: O(k)** for the heap itself, plus O(N) for the output
  buffer (the output space is unavoidable for any merge method).

For this run: k = 3, N = 12 → the program measured
**21 comparisons** and **24 heap operations** (12 inserts + 12 extract-mins).
This matches the theoretical bound: N·log₂(k) ≈ 12 × 1.58 ≈ 19, and the
extra initial-build comparisons bring it to 21 — consistent with O(N log k).

---

## (b) Simple Pairwise Merging

**How it works:** merge the lists two at a time using the standard 2-way
merge routine — first L1 with L2 to get an intermediate list of size 2n,
then that result with L3, and so on, for k−1 passes total.

- Each 2-way merge of two lists of combined size m costs O(m) comparisons.
- Pass 1 merges L1 (n) and L2 (n) → cost O(2n)
- Pass 2 merges the result (2n) with L3 (n) → cost O(3n)
- Pass i merges a list of size i·n with the next list of size n
  → cost O((i+1)·n)
- Summing over k−1 passes:
  O(2n + 3n + 4n + ... + kn) = O(n · (2+3+...+k)) = **O(n·k²)**, i.e.
  **O(N·k)** since N = nk.
- **Total time complexity: O(N·k)**
- **Space complexity: O(N)** — an intermediate array is needed after each
  pass (can be reduced to O(n) extra space per pass, but total output is
  still O(N)).

For this run: k = 3, N = 12 → the program measured
**7 comparisons** in Pass 1 and **11 comparisons** in Pass 2, **18 total**,
consistent with O(N·k) for small k (12 × 3 = 36 as a loose upper bound;
the actual count is lower because early-exhaustion of a list skips some
comparisons).

---

## Summary Table

| Metric                       | Min-Heap Merge          | Pairwise Merge         |
|-------------------------------|--------------------------|--------------------------|
| Time complexity                | O(N log k)                | O(N·k)                    |
| Space (auxiliary structure)    | O(k)                      | O(N)                      |
| Comparisons (this run, k=3,N=12)| 21                       | 18                        |
| Number of "rounds"              | N extract-min operations | k−1 merge passes          |

**Note on k = 3:** with only 3 lists, log₂k ≈ 1.58 is close to k itself, so
the two approaches perform similarly on this small input (21 vs 18
comparisons) — pairwise merging can even edge out the heap slightly on
comparisons here, though it does more data movement (it copies elements
into intermediate arrays at every pass, giving it O(N) extra space, and
the O(N) elements are touched k−1 times as they move to bigger and bigger
intermediate lists — i.e., N·k total element accesses vs. N total heap
operations for the heap approach). The two methods diverge sharply as
k grows (see Part c below).
