# Micro-benchmarks

- Machine: Intel(R) Core(TM) i7-4770
- Compiler: GCC 8.3.1, `-DNDEBUG -O3 -m64 -march=native`
- MKL: 2019.0.5, sequential ILP64

---

## Arrays

### [Sequential reads/writes](src/array/seq_read_write/)

![Sequential reads/writes](src/array/seq_read_write/read_write.png)

### [Reverse](src/array/reverse/)

![Reverse](src/array/reverse/reverse.png)

---

## Matrices

### [Matrix copy with transposition](src/matrix/copy/)

![Matrix copy with transposition](src/matrix/copy/copy.png)

### [Matrix 90 deg rotation](src/matrix/rotate/)

![Matrix 90 deg rotation](src/matrix/rotate/rotate.png)

<!-- ## Arrays

### Rotation

Algorithms:
* (S) `std::rotate`
* (D) Dolphin (one cyclic shift of each cycle)
* (G) Gries&ndash;Mills (swapping blocks)
* (R) Using three reverses
* (C) Direct copy using an additional memory buffer

Results for `std::vector` with `N` elements of type `int`.

| N           | Num. bytes | (S) | (D1)   | (D2)   | (G1)  | (G2)  | (R)   | (C1)  | (C2)  |
|:------------|:-----------|:---:|:------:|:------:|:-----:|:-----:|:-----:|:-----:|:-----:|
| 32          | 128        | 1   | 1.31   | 1.53   | 0.82  | 0.88  | 0.72  | 1.12  | 1.07  |
| 64          | 256        | 1   | 1.55   | 1.89   | 1.10  | 1.11  | 0.67  | 0.95  | 0.90  |
| 128         | 512        | 1   | 1.81   | 2.28   | 1.31  | 1.36  | 0.57  | 0.80  | 0.78  |
| 256         | 1 K        | 1   | 2.34   | 3.05   | 1.65  | 1.92  | 0.57  | 0.70  | 0.68  |
| 512         | 2 K        | 1   | 2.75   | 3.61   | 2.13  | 2.42  | 0.56  | 0.66  | 0.69  |
| 1'024       | 4 K        | 1   | 3.04   | 4.08   | 2.51  | 2.86  | 0.53  | 0.56  | 0.57  |
| 2'048       | 8 K        | 1   | 3.50   | 4.78   | 3.03  | 3.41  | 0.76  | 0.57  | 0.66  |
| 4'096       | 16 K       | 1   | 3.91   | 5.44   | 3.53  | 3.88  | 0.86  | 0.59  | 0.70  |
| 8'192       | 32 K       | 1   | 4.19   | 5.86   | 3.93  | 4.29  | 0.92  | 1.14  | 1.25  |
| 16'384      | 64 K       | 1   | 8.10   | 8.50   | 4.07  | 4.30  | 1.32  | 1.27  | 1.30  |
| 32'768      | 128 K      | 1   | 8.49   | 8.57   | 3.54  | 3.78  | 1.22  | 1.16  | 1.17  |
| 65'536      | 256 K      | 1   | 8.45   | 8.43   | 3.18  | 3.39  | 1.15  | 1.31  | 1.33  |
| 131'072     | 512 K      | 1   | 8.00   | 8.02   | 2.73  | 2.90  | 1.20  | 1.21  | 1.18  |
| 262'144     | 1 M        | 1   | 7.65   | 7.69   | 2.48  | 2.61  | 1.12  | 1.10  | 1.07  |
| 524'288     | 2 M        | 1   | 7.44   | 7.45   | 2.37  | 2.50  | 1.07  | 1.05  | 1.04  |
| 1'048'576   | 4 M        | 1   | 7.38   | 7.39   | 2.30  | 2.41  | 1.04  | 1.21  | 1.21  |
| 2'097'152   | 8 M        | 1   | 18.90  | 20.31  | 1.93  | 2.03  | 1.18  | 1.60  | 1.66  |
| 4'194'304   | 16 M       | 1   | 15.80  | 16.33  | 1.31  | 1.37  | 1.19  | 1.21  | 1.21  |
| 8'388'608   | 32 M       | 1   | 14.97  | 16.41  | 1.17  | 1.19  | 1.19  | 1.04  | 1.02  |
| 16'777'216  | 64 M       | 1   | 17.32  | 16.81  | 1.10  | 1.11  | 1.10  | 1.49  | 1.25  |
| 33'554'432  | 128 M      | 1   | 19.52  | 20.30  | 1.05  | 1.08  | 1.05  | 1.68  | 1.58  |
| 67'108'864  | 256 M      | 1   | 22.63  | 22.33  | 1.08  | 1.08  | 1.05  | 1.44  | 1.23  |

## Matrices

### 90 degrees rotation

Algorithms:
* (C) Cyclic permutation of 4 elements groups
* (T) Transposition + flip
* (D) Direct copy using an additional memory buffer

Results for square matrices `N * N` (X) and `(N - 1) * (N - 1)` (X') of type `int`.

| N      | Elements   | Bytes   | (C)  | (T)   | (D)   | (C')  | (T')  | (D')  |
|:-------|:---------- |:------: |:----:|:-----:|:-----:|:-----:|:-----:|:-----:|
| 9      |81          | 324     | 1    | 1.87  | 3.06  | 0.83  | 1.53  | 2.71  |
| 17     |289         | ~1 K    | 1    | 1.61  | 2.05  | 0.76  | 1.43  | 1.73  |
| 33     |1'089       | ~4 K    | 1    | 1.90  | 2.01  | 0.85  | 1.77  | 1.91  |
| 65     |4'225       | ~16 K   | 1    | 2.00  | 1.89  | 0.94  | 1.95  | 1.98  |
| 129    |16'641      | ~65 K   | 1    | 2.00  | 1.68  | 2.24  | 3.23  | 2.81  |
| 257    |66'049      | ~258 K  | 1    | 1.65  | 1.40  | 2.46  | 5.60  | 3.24  |
| 513    |263'169     | ~1 M    | 1    | 1.50  | 0.79  | 1.63  | 4.40  | 2.05  |
| 1'025  |1'050'625   | ~4 M    | 1    | 1.15  | 0.61  | 1.24  | 1.99  | 1.19  |
| 2'049  |4'198'401   | ~16 M   | 1    | 1.17  | 2.11  | 1.07  | 1.69  | 2.53  |
| 4'097  |16'785'409  | ~64 M   | 1    | 1.06  | 2.31  | 1.47  | 1.80  | 2.50  |
| 8'193  |67'125'249  | ~256 M  | 1    | 1.04  | 2.06  | 1.26  | 1.63  | 2.29  |
 -->
