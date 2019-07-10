# gss
Grep for Small Strings.

## Background

The `grep` command on unix based operating systems implements the [Boyer-Moore](https://en.wikipedia.org/wiki/Boyer%E2%80%93Moore_string-search_algorithm) string searching algorithm in order to execute its pattern matching. The problem with Boyer-Moore is that as pattern size decreases, the algorithm takes longer to run. This can significantly slow down people wanting to match small strings in large portions of text, for example those found in DNA sequencing.

I am implementing the [Knuth-Morris-Pratt](https://en.wikipedia.org/wiki/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm) (KMP) pattern matching algorithm, and the [Rabin-Karp](https://en.wikipedia.org/wiki/Rabin%E2%80%93Karp_algorithm) pattern matching algorithm. The end goal is to achieve a faster runtime than Unix `grep` when searching for small strings (eg. those found in DNA sequencing, such as `ACGT`).

### Why implement two algorithms?

The problem with KMP is that it has a [space complexity](https://en.wikipedia.org/wiki/Space_complexity) of `O(len text)`, and this means that if there is a very long portion of text which needs to be read, gss would segfault - if it only implemented KMP. As such, the Rabin-Karp algorithm has also been implemented, because it has a space complexity of `O(1)`. The idea is that KMP will be run on every line of reasonable length, and when an exceptionally large line is encountered, Rabin-Karp will be run to prevent segfault.

Realistically, there shouldn't be lines which will cause the KMP algorithm to crash, but in the most unlikely instance that there *is*, Rabin-Karp has also been implemented as a failsafe.

## Benchmarks

Benchmarks will be put up here when a command line interface of some form has been written.