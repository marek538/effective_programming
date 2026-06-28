# Algorithmic Challenges & Data Structures
Unfortunately, I no longer have access to the exact tasks. In the list below, you can find approximately what each task tries to solve.

## 1. Unique K-Permutations (Anagram)
### Problem
Generate all unique k-length permutations from a string containing duplicate characters without producing redundant overlapping states.
### Solution
Implemented backtracking guided by a character frequency map to natively prune identical recursive branches before they are explored.

## 2. BST Topologies (Ceiling)
### Problem
Determine the number of uniquely shaped Binary Search Trees (BST) generated from multiple different sequences of integer insertions.
### Solution
Serialized the topology of each generated tree into a normalized string representation and utilized a hash set to efficiently count unique structural shapes.

## 3. Vehicle Routing (Convoy)
### Problem
Partition a sequential list of vehicles into weight-constrained convoys to minimize total travel time, where each convoy's speed is dictated by its slowest vehicle.
### Solution
Applied Dynamic Programming with memoization to evaluate all valid sequential groupings and identify the optimal time partitioning.

## 4. Bounding Box Collision (Intersect)
### Problem
Determine whether an arbitrary 2D line segment intersects with a given axis-aligned rectangle (bounding box).
### Solution
Utilized computational geometry vectors (cross products for orientation) to check segment intersections against the rectangle's borders and internal area.

## 5. Bidirectional Coin Exchange (Money)
### Problem
Find a valid exact payment combination given a strictly limited pool of specific coin denominations for both the buyer and the seller.
### Solution
Implemented algorithmic state searches over frequency maps representing the available coin inventories of both parties to resolve the exact exchange.

## 6. Piggy Bank (Unbounded Knapsack)
### Problem
Calculate the minimum possible monetary value inside a piggy bank based on its exact net weight and a defined set of coin weights and values.
### Solution
Used a variation of the Unbounded Knapsack Dynamic Programming algorithm to track the minimum value required to achieve every exact weight increment up to the target.

## 7. AST Parser (Polish Notation)
### Problem
Parse a mathematical expression provided in prefix (Polish) notation and reconstruct its logical structure.
### Solution
Constructed an Abstract Syntax Tree (AST) by sequentially parsing operators and operands into nodes, allowing for proper structural traversal and conversion.

## 8. Segmented Path Traversal (Ponorka)
### Problem
Calculate the exact number of fixed-length strides required to traverse a multi-segmented geometric path.
### Solution
Iteratively projected the residual stride distance across corner transitions utilizing mathematical distance formulas (Pythagorean theorem).

## 9. Hexadecimal Compression (Quadtrees)
### Problem
Decode and manipulate 2D graphical data that has been heavily compressed into a hexadecimal quadtree bitstream.
### Solution
Developed a recursive bitwise parser that converts hexadecimal streams into binary, constructs a hierarchical quadrant tree, and rasterizes it back into a 2D matrix.

## 10. Sliding Window Aggregation (Samples)
### Problem
Compute real-time aggregate statistics (e.g., minimum or maximum) over a continuously updating sliding time window of data samples.
### Solution
Implemented an object-oriented stream processor utilizing min/max heaps (priority queues) to efficiently maintain and query the active window state in logarithmic time.

## 11. Target Sequence Matching (Shooting Gallery)
### Problem
Find the maximum number of paired targets (a variation of the Longest Palindromic Subsequence problem) within a sequential dataset.
### Solution
Applied 2D dynamic programming to evaluate overlapping subproblems across all interval lengths, finding the optimal sequence match in $O(n^2)$ time complexity.

## 12. Triangular Grid Navigation (Triangle)
### Problem
Model and traverse a discrete triangular grid to evaluate neighboring cells, structural orientation, and spatial dependencies.
### Solution
Designed a custom 2D data structure with specialized index-mapping algorithms to accurately resolve adjacencies and inversions within a non-orthogonal coordinate system.

## 13. Container Sorting (Baggage)
### Problem
Calculate the exact number of operations required to reorganize a stack of containers governed by strict movement rules.
### Solution
Leveraged the mathematical properties of the Towers of Hanoi ($2^n - 1$) to algorithmically compute the minimum required moves without simulating the entire state space.
