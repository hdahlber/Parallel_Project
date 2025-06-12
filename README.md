# Parallel_Project
Final Project Submission

Carl Nordernbrink, Hektor Dahlberg

We have generated 40 instances of arrays of sizes 100, 1000, 100000, and 1000000, for 10 instances of each.
Each array element is an integer with a random value ranging between 0 and 1000000.
We have then applied a quicksort implementation for each of the arrays twice: one with a naive implementation and one with a parallel implementation.
Using this programme we can conclude that the parallel implementation is faster than the naive implementation for larger arrays, but slower for smaller arrays.
The quicksort can be benefitted by a parallell implementation with improvements as large as 2x if the array size is in the millions but is slower for arrays with sizes in the tens of thousands or smaller.


## Table: comparison of average execution times (10 samples) for naive and parallell implementations of quicksort
| Array Size   | Naive Time (ms) | Parallel Time (ms) | Improvement |
|--------------|-----------------|--------------------|-------------|
| 100          | 0.011           | 3.717              | 0.003x	    |
| 1000         | 0.155           | 4.749              | 0.033x      |
| 100000       | 21.987          | 16.796             | 1.309x      |
| 1000000      | 283.419         | 141.742            | 2.000x      |