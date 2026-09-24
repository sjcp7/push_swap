*This project has been created as part of the 42 curriculum by ljanuari, samupedr[/].*

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

The disorder of the initial stack is measured **before any move is performed**, as
the ratio of inverted pairs to the total number of pairs (a value between 0 and 1):

```
disorder(a) = |{ (i, j) : i < j and a[i] > a[j] }| / (n * (n - 1) / 2)
```

An optional `--bench` flag prints a full report to **stderr** — disorder (with two
decimal places), the selected strategy and its complexity class, the total number of
operations and per-operation counts — without polluting the operation stream on
stdout.

## Building and Usage

```
make            # builds ./push_swap
make bonus      # builds the bonus ./checker
```

```
./push_swap [--simple|--medium|--complex|--adaptive] [numbers...]
./push_swap --bench [--simple|--medium|--complex|--adaptive] [numbers...]
```

Flags may be given in **any order**, but at most one strategy flag and one
`--bench` may be provided. The first argument is the top of the stack. Error
handling: non-integer arguments, values outside the `int` range, duplicates, and
empty/blank arguments (`""` or `"   "`) make the program print `Error` followed by
a newline on **stderr**. (Rejecting empty/blank arguments is a deliberate choice:
it matches the strictness of the reference checker binary.)

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
complexity classes below are stated in the **Push_swap operation model**, i.e. they
measure the number of generated operations, as required by the subject. Auxiliary
space is `O(n)` in all strategies (the two stacks plus normalization and the output
buffer); no global variables are used.

### 1. Simple strategy — Selection Sort adaptation — O(n²)

The classic selection sort idea, adapted to two stacks: repeatedly find the **minimum**
of `a`, bring it to the top rotating the **shortest way** (`ra` or `rra`, whichever
needs fewer moves — the `reverse_op` helper flips the direction when the index is
past half the stack), push it to `b`; when only the maximum is left on `a`, push
everything back with `pa`. Because the minimums are pushed in increasing order, `b`
holds them in decreasing order from bottom to top, so the final `pa` sweep rebuilds
a sorted `a` with no extra positioning.

**Complexity argument (upper bound).** To extract an element from a stack of `m`
elements costs at most `⌊m/2⌋` rotations (shortest direction) plus 1 `pb`. Summing
over the `n-1` extractions plus the final push-back:

```
T(n) ≤ Σ_{m=2}^{n} (⌊m/2⌋ + 1) + (n - 1)
     ≤ (1/2)·Σ_{m=1}^{n} m + 2n
     = n(n + 1)/4 + 2n
     = O(n²)
```

Justification: trivially correct, almost no extra state, and cheap on nearly-sorted
inputs where each minimum is already close to the top — exactly the profile the
adaptive strategy exploits for `disorder < 0.2`.

### 2. Medium strategy — Chunk Sort — O(n√n)

Chunk sort is a **range-based partitioning** method over the normalized ranks. The
rank space `0..n-1` is sliced into contiguous ranges of width

```
w = ⌊1.5 · √n⌋          (implemented as (ps_sqrt(n) * 3) / 2)
```

Chunks are a pure concept over ranks, not physical containers: the algorithm keeps a
growing threshold `k = w, 2w, 3w, ...` and, for each threshold, pushes up to `w`
elements whose rank is `< k` from `a` to `b` — i.e. rank `0..w-1` leave first, then
`w..2w-1`, and so on until `a` is empty. Each element is reached by scanning `a`
from both ends and rotating the **shortest way**. Since elements enter `b` in global
rank order, `b` stays nearly sorted, and a final pass (`find_max` + `pa`) rebuilds
a sorted `a`. The `1.5` factor on the chunk width is an empirical optimization of
the total operation count.

**Complexity argument (upper bound).** With `w = ⌊1.5√n⌋` there are
`⌈n/w⌉ ≤ (2/3)√n + 1` thresholds. For each threshold the stack is scanned at most
once (`≤ n` rotations total per threshold, because every rotation step brings a new
element to the top), and each element is pushed exactly once (`n` `pb`'s) and pushed
back once (`n` `pa`'s):

```
T(n) ≤ n·⌈n/w⌉ + n + n
     ≤ n·((2/3)√n + 1) + 2n
     = (2/3)·n√n + 3n
     = O(n√n)
```

Justification: chunking converts one "global" sort into `≈ √n` almost-local passes,
which is the sweet spot between the simplicity of O(n²) methods and the bitwise
machinery of radix sort. It dominates on medium-disorder inputs.

### 3. Complex strategy — Radix Sort (LSD, base 2) — O(n log n)

After normalization every value is a rank in `0..n-1`, representable with
`b = ⌈log₂(n-1)⌉` bits. The algorithm performs **b least-significant-bit passes**:
on pass `k`, elements with bit `k` equal to 0 are pushed to `b`, elements with bit
`k` equal to 1 stay on `a` (rotated), and then everything is pushed back to `a` —
a stable binary partition by bit `k`. After `b` passes the stack is sorted. When `n`
is a power of two, the extra pass where every bit would be 0 is skipped (the largest
normalized value is `n - 1`).

**Complexity argument (upper bound).** Each pass moves every element exactly once to
`b` (`n` `pb`'s) and once back (`n` `pa`'s), so each pass costs exactly `2n`
operations, and there are `⌈log₂(n-1)⌉` passes:

```
T(n) = 2n · ⌈log₂(n-1)⌉
     ≤ 2n·log₂ n
     = O(n log n)
```

Justification: radix sort gives a **distribution-independent** near-linearithmic
count — the number of passes depends only on the bit length, never on how scrambled
the input is. This is the strongest worst-case guarantee of the three, which is why
the adaptive strategy reserves it for the hardest inputs (`disorder ≥ 0.5`).

### 4. Adaptive strategy — disorder-based selection

The adaptive strategy measures the disorder `d` of the initial stack **before any
move** and dispatches to the internal method best suited for that regime
(see `compute_strategy`):

| Regime | Internal method | Class (Push_swap model) |
|---|---|---|
| `d < 0.2` | Selection Sort adaptation | O(n²), tiny constant on nearly-sorted inputs |
| `0.2 ≤ d < 0.5` | Chunk Sort | O(n√n) |
| `d ≥ 0.5` | Radix Sort | O(n log n) |

**Threshold rationale.** `0.5` is the subject-mandated boundary: at and above it the
chosen method must run in O(n log n), which radix sort guarantees. `0.2` is the
empirically measured crossing point between the two cheaper methods: below it, the
quadratic method's extraction cost (a few rotations per element, and an immediate
exit through the `is_sorted` guard on sorted input) is smaller than the fixed price
chunk sort always pays for its `√n` passes; above it, the quadratic cost grows
linearly with disorder while the chunk count stays at `≈ (2/3)√n`, so the O(n√n)
method is strictly cheaper. Each regime therefore respects its required complexity
target in the Push_swap operation model.

## The Buffer Manager

Internally, generated operations are not written to stdout one syscall at a time.
Every operation is appended as an enum value to a **dynamically growing buffer**
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
the output contains **only** operations separated by `\n`), the `--bench` statistics
(total and per-operation counts are computed from the same enum stream during the
flush), and a measurable reduction of the final operation count. Allocation failure
at any growth step is handled gracefully through `ps_abort` (no leaks, no partial
output).

## Bonus — checker

`make bonus` builds `checker`, which takes the stack as argument (first argument at
the top), reads operations from standard input with our own `get_next_line`,
executes them, and prints `OK` if `a` is sorted and `b` is empty, `KO` otherwise.
Invalid arguments, duplicates, unknown or malformed instructions print `Error` on
stderr. Like the push_swap parser, the checker **rejects empty and blank arguments**
(`""`, `"   "`), matching the strictness of the reference binary.

## AI Usage and Resources

We used AI tools (chat-based assistants) **exclusively as consultants** during this
project: to discuss algorithmic ideas, review design trade-offs and sanity-check test
strategies. We never asked AI for ready-made project code, and no code in this
repository was copied from an AI output; every line was written, reviewed and is
fully understood by ljanuari and samupedr.

Principal source of inspiration for the choice and adaptation of the sorting
algorithms:
[GeeksforGeeks — Selection Sort](https://www.geeksforgeeks.org/dsa/selection-sort-algorithm-2/)
(alongside the 42 subject's own complexity constraints).

## Authors

- **ljanuari** (Leosnane Januario) — chunk sort, disorder metric & benchmark output,
  buffer manager, stack operations, initial parsing
- **samupedr** (Samuel Pedro) — radix sort, merge sort normalizer, selection sort
  refinements, Makefile, checker + get_next_line, parser (flags in any order, strict
  blank-argument rejection), error handling

42 Luanda — 2026
