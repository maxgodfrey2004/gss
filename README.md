# gss
Grep for Small Strings.

## Background

The `grep` command on unix based operating systems implements the [Boyer-Moore](https://en.wikipedia.org/wiki/Boyer%E2%80%93Moore_string-search_algorithm) string searching algorithm in order to execute its pattern matching. The problem with Boyer-Moore is that as pattern size decreases, the algorithm takes longer to run.

I am implementing the [Knuth-Morris-Pratt](https://en.wikipedia.org/wiki/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm) (KMP) pattern matching algorithm in order to see if I can achieve a faster runtime than Unix `grep` when searching for small strings (eg. those found in DNA sequencing, such as `ACGT`).

Benchmarks will be added here when I have implemented the KMP algorithm.
