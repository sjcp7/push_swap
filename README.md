*This project has been created as part of the 42 curriculum by ljanuari, samupedr.*

# push_swap

## Description

**push_swap** is a 42 algorithm project whose goal is to sort a stack of integers
(`stack a`) using a second auxiliary stack (`stack b`) and a very limited set of
operations (`sa`, `sb`, `ss`, `pa`, `pb`, `ra`, `rb`, `rr`, `rra`, `rrb`, `rrr`).
The program must print the **shortest possible sequence of operations** that sorts
`stack a` in ascending order, with the smallest element on top.

The project is deliberately constrained: there is no random access, no cheap way to
insert an element at an arbitrary position, and every action is counted. The real
challenge is therefore not "sorting numbers" but choosing the algorithm whose
*operation count* scales best for each input configuration. To enforce this, the
subject requires **four distinct sorting strategies** embedded in a single binary,
selected at runtime:

| Strategy flag | Complexity class (Push_swap operation model) |
|---|---|
| `--simple` | O(n²) — Selection Sort adaptation |
| `--medium` | O(n√n) — Chunk Sort |
| `--complex` | O(n log n) — Radix Sort (LSD, base 2) |
| `--adaptive` (default) | selects an internal method based on the measured **disorder** of the input |

## Disorder Metric

The disorder of the initial stack is measured before any move is performed,
as the ratio of inverted pairs to the total number of pairs:

$$
\text{disorder}(a) = \frac{\text{number of inversions}}{\text{total pairs}}
                   = \frac{|\{\,(i,j) : i < j \text{ and } a[i] > a[j]\,\}|}{\dfrac{n\,(n-1)}{2}}
$$

The result is a value between `0` (already sorted) and `1` (fully reversed),
used by the adaptive strategy to pick the internal method:

| Disorder `d` | Internal method | Class (Push_swap model) |
|---|---|---|
| `d < 0.2` | Selection Sort adaptation | O(n²) |
| `0.2 ≤ d < 0.5` | Chunk Sort | O(n√n) |
| `d ≥ 0.5` | Radix Sort | O(n log n) |

An optional `--bench` flag prints a full report to **stderr** — disorder (with two
decimal places), the selected strategy and its complexity class, the total number of
operations and per-operation counts — without polluting the operation stream on
stdout.

## Instructions

```
make            # builds ./push_swap
make bonus      # builds the bonus ./checker
```

```
./push_swap [--simple|--medium|--complex|--adaptive] [numbers...]
./push_swap --bench [--simple|--medium|--complex|--adaptive] [numbers...]
```

Flags may be given in any order, but at most one strategy flag and one
`--bench` may be provided. The first argument is the top of the stack. Error
handling: non-integer arguments, values outside the `int` range, duplicates, and
empty/blank arguments (`""` or `"   "`) make the program print `Error` followed by
a newline on **stderr**.
Examples:

```
$> ./push_swap --simple 5 4 3 2 1
$> ARG="4 67 3 87 23"; ./push_swap --bench --adaptive $ARG 2> bench.txt | ./checker $ARG
OK
$> cat bench.txt
[bench] disorder:  40.00%
[bench] strategy:  Adaptive / O(n√n)
[bench] total_ops: 7
...
```

## Algorithm Selection and Justification

All input numbers are first **normalized** (rank-compressed to `0 .. n-1` with a
merge sort), so that every algorithm works on ranks instead of raw values. The
complexity classes below are stated in the Push_swap operation model, i.e. they
measure the number of generated operations. Auxiliary space is `O(n)` in all strategies (the two stacks plus normalization and the output buffer).

### 1. Simple strategy — Selection Sort adaptation — O(n²)

The classic selection sort idea, adapted to two stacks: repeatedly find the minimum
of `a`, bring it to the top rotating the **shortest way** (`ra` or `rra`, whichever
needs fewer moves), push it to `b`; when only the maximum is left on `a`, push
everything back with `pa`. Because the minimums are pushed in increasing order, `b`
holds them in decreasing order from bottom to top, so the final `pa` sweep rebuilds
a sorted `a` with no extra positioning.

**Complexity argument (Intuitive derivation):**
* Finding and moving the minimum in a stack of size $k$ takes at most $k/2$ rotations.
* Summing this cost over all $n$ elements:

$$T(n) = \sum_{k=1}^{n} \frac{k}{2} + n = \frac{n(n + 1)}{4} + n = \frac{n^2}{4} + \frac{5n}{4}$$

* Dropping lower-order terms and constant coefficients yields **$\mathcal{O}(n^2)$**.

This algorithm was picked for its ease of implementation. It is intuitive, too.

---

### 2. Medium strategy — Chunk Sort — O(n√n)

Chunk sort partitions the $n$ normalized ranks into $S$ chunks of width $W = n / S$.

**Complexity argument (Optimization via derivative):**
The total operation count $T(n, S)$ is governed by two main costs:
1. **Scanning Stack A**: Scanning `a` to extract elements for $S$ chunks takes at most $n$ rotations per chunk pass $\implies S \cdot n$ operations.
2. **Positioning in Stack B**: Inserting each of the $n$ elements into its position in `b` (size $W$) takes on average $W/2 = n / (2S)$ rotations $\implies n \cdot \frac{n}{2S} = \frac{n^2}{2S}$ operations.

Summing both costs gives:

$$T(n, S) = S \cdot n + \frac{n^2}{2S}$$

To find the optimal number of chunks $S$ that minimizes total operations, we take the derivative of $T$ with respect to $S$ and set it to zero:

$$\frac{dT}{dS} = n - \frac{n^2}{2S^2} = 0 \implies n = \frac{n^2}{2S^2} \implies S^2 = \frac{n}{2} \implies S = \sqrt{\frac{n}{2}}$$

Substituting $S = \sqrt{n / 2}$ back into the cost equation:

$$T(n) = \left(\sqrt{\frac{n}{2}}\right) \cdot n + \frac{n^2}{2\sqrt{n/2}} = \sqrt{2} \cdot n\sqrt{n} = \mathbf{\mathcal{O}(n\sqrt{n})}$$

We picked this one because it was the more fun one to implement. :)

---

### 3. Complex strategy — Radix Sort (LSD, base 2) — O(n log n)

Operates on normalized ranks ($0$ to $n-1$) using base-2 bitwise operations.

**Complexity argument:**
* **Bit passes**: Representing values up to $n-1$ in binary requires $B = \lceil \log_2 n \rceil$ bits.
* **Cost per pass**: Every pass checks all $n$ elements in `a` ($n$ operations: `ra` or `pb`) and pushes them back from `b` to `a` ($n$ operations: `pa`), costing exactly $2n$ operations per bit.
* **Total Cost**:

$$T(n) = 2n \cdot \lceil \log_2 n \rceil \approx 2n \log_2 n = \mathbf{\mathcal{O}(n \log n)}$$

This binary version translates very well to the push_swap double stack model, so we felt it was natural to implement and comprehend.

### 4. Adaptive strategy — disorder-based selection

The adaptive strategy measures the disorder `d` of the initial stack before any
move and dispatches to the internal method best suited for that regime. 
Given that the subject explicitly mandates specific complexity classes for each threshold, we decided to just route between the aforementioned algorithms:

| Regime | Internal method | Class (Push_swap model) |
|---|---|---|
| `d < 0.2` | Selection Sort adaptation | O(n²), tiny constant on nearly-sorted inputs |
| `0.2 ≤ d < 0.5` | Chunk Sort | O(n√n) |
| `d ≥ 0.5` | Radix Sort | O(n log n) |

## The Buffer Manager

Internally, generated operations are not written to stdout at operation time.
Every operation is appended as an enum value to a dynamically growing buffer
(`buffer_push`, capacity doubling via `buffer_realloc`), which is processed and
flushed exactly once at the end (`buffer_flush`). Before flushing, a simplification
pass (`buffer_simplify`, applied until fixpoint) shortens the stream by applying
local rewrite rules to adjacent operations:

- **Cancellation**: `sa sa`, `sb sb`, `ss ss`, `pa pb` / `pb pa`, `ra rra` /
  `rra ra`, `rb rrb` / `rrb rb`, `rr rrr` / `rrr rr` → both removed;
- **Merging**: `sa sb` / `sb sa` → `ss`, `ra rb` / `rb ra` → `rr`,
  `rra rrb` / `rrb rra` → `rrr`, `rr rra` → `rb`, `rr rrb` → `ra`,
  `rrr ra` → `rrb`, `rrr rb` → `rra`.

The buffer manager gives us three things: a clean stdout stream (one final flush, so
the output contains only operations separated by `\n`), the `--bench` statistics
(total and per-operation counts are computed from the same enum stream during the
flush), and a measurable reduction of the final operation count. Allocation failure
at any growth step is handled through `ps_abort`.

## Bonus: The checker

`make bonus` builds `checker`, which takes the stack as argument (first argument at
the top), reads operations from standard input with our own `get_next_line`,
executes them, and prints `OK` if `a` is sorted and `b` is empty, `KO` otherwise.
Invalid arguments, duplicates, unknown or malformed instructions print `Error` on
stderr. 

## Resources

We used AI tools (chat-based assistants) as consultants during this project: to discuss algorithmic ideas, review design trade-offs and sanity-check test strategies, as well as to draft most of this README.

Principal source of inspiration for the choice and adaptation of the sorting
algorithms:
[GeeksforGeeks](https://www.geeksforgeeks.org/)
(alongside the 42 subject's own complexity constraints).

We also used a [Push Swap Visualizer](https://push-swap-visualizer.vercel.app/).

## Contribution

- **ljanuari** (Leosnane Januario) — chunk sort, merge sort normalizer, disorder metric, benchmark, get_next_line implementation
  output, buffer manager, stack operations, initial parsing
- **samupedr** (Samuel Pedro) — complexity calculation and review, radix sort, selection sort, refinements, Makefile, checker, error handling, bug chasing
