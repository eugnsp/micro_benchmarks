# Micro-benchmarks

## Arrays

### Rotations

Algorithms:
* (1) Dolphin (one cyclic shift of each cycle)
* (2) Gries&ndash;Mills (swapping blocks)
* (3) Using three reverses
* (4) Direct copy using an additional memory buffer

## Matrices

### 90 degrees rotation

Algorithms:
* (1) Cyclic permutation of 4 elements groups
* (2) Transposition + flip
* (3) Direct copy using an additional memory buffer

Results for square matrices `N * N` [Alg(i)] and `(N - 1) * (N - 1)` [Alg(i-)] of `int`s.

| N      | # elements | # bytes  | Alg(1) | Alg(2) | Alg(3) | Alg(1-) | Alg(2-) | Alg(3-) |
|:-------|:-----------|:--------:|:------:|:------:|:------:|:-------:|:-------:|:-------:|
| 9      |81          | 324      | 1      | 1.87   | 3.06   | 0.83    | 1.53    | 2.71    |
| 17     |289         | ~1 K     | 1      | 1.61   | 2.05   | 0.76    | 1.43    | 1.73    |
| 33     |1'089       | ~4 K     | 1      | 1.90   | 2.01   | 0.85    | 1.77    | 1.91    |
| 65     |4'225       | ~16 K    | 1      | 2.00   | 1.89   | 0.94    | 1.95    | 1.98    |
| 129    |16'641      | ~65 K    | 1      | 2.00   | 1.68   | 2.24    | 3.23    | 2.81    |
| 257    |66'049      | ~258 K   | 1      | 1.65   | 1.40   | 2.46    | 5.60    | 3.24    |
| 513    |263'169     | ~1 M     | 1      | 1.50   | 0.79   | 1.63    | 4.40    | 2.05    |
| 1'025  |1'050'625   | ~4 M     | 1      | 1.15   | 0.61   | 1.24    | 1.99    | 1.19    |
| 2'049  |4'198'401   | ~16 M    | 1      | 1.17   | 2.11   | 1.07    | 1.69    | 2.53    |
| 4'097  |16'785'409  | ~64 M    | 1      | 1.06   | 2.31   | 1.47    | 1.80    | 2.50    |
| 8'193  |67'125'249  | ~256 M   | 1      | 1.04   | 2.06   | 1.26    | 1.63    | 2.29    |

