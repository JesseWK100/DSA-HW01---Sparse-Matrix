# 🏷️ Sparse Matrix Operations Library

[![Build Status](https://img.shields.io/badge/build-passing-brightgreen)](https://github.com/yourusername/sparse-matrix)
[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)
\[![C++ Version](https://img.shields.io/badge/C%2B%2B-11-blueviolet)]

---

## ✨ Project Overview

Welcome to the **Sparse Matrix Operations Library**, a lightweight C++ toolkit designed to handle large, sparse matrices efficiently. Whether you need to **add**, **subtract**, or **multiply** huge matrices without wasting memory on zeros, this library has you covered!

🚀 **Why Sparse Matrices?**

* Save memory by only storing nonzero entries.
* Increase speed by skipping zero-valued operations.
* Essential for scientific computing, machine learning, and graph algorithms.

---

## 📋 Table of Contents

1. [Features](#-features)
2. [Prerequisites](#-prerequisites)
3. [Installation & Setup](#-installation--setup)
4. [Usage Guide](#-usage-guide)

   * [Compiling the Code](#compiling-the-code)
   * [Running the Program](#running-the-program)
5. [File Format & Sample Data](#-file-format--sample-data)
6. [Handling Header Mismatches](#-handling-header-mismatches)
7. [Project Structure](#-project-structure)
8. [Algorithmic Details](#-algorithmic-details)
9. [Performance & Efficiency](#-performance--efficiency)
10. [Contributing](#-contributing)
11. [License](#-license)
12. [Contact & Support](#-contact--support)

---

## 🌟 Features

* **Sparse Storage**: Per-row sorted vectors of `(column, value)` pairs.
* **Operations Supported**:

  * **Addition** `matrixC = A + B`
  * **Subtraction** `matrixC = A - B`
  * **Multiplication** `matrixC = A * B`
* **Robust Parsing**: Reads files in the format:

  ```text
  rows=<num_rows>
  cols=<num_cols>
  (r, c, value)
  ```
* **Error Handling**: Detects malformed input, dimension mismatches, and out-of-bounds indices.
* **Lightweight**: No external dependencies; pure C++11 standard library.

---

## 🛠️ Prerequisites

* **Compiler**: `g++ (GCC) >= 4.8` or any C++11-compliant compiler
* **Platform**: Linux, macOS, or Windows (with MinGW/Cygwin)

---

## ⚙️ Installation & Setup

1. **Clone the repository**

   ```bash
   git clone https://github.com/JesseWK100/DSA-HW01---Sparse-Matrix.git
   cd sparse-matrix
   ```

2. **Compile the source**

   ```bash
   g++ -std=c++11 -O2 SparseMatrix.cpp -o sparse
   ```

3. **Prepare your input files**

   * Place your sample `.txt` files in `sample_inputs/`

---

## 🎮 Usage Guide

### 🏗️ Compiling the Code

```bash
# From the project root
g++ -std=c++11 -O2 SparseMatrix.cpp -o sparse
```

### ▶️ Running the Program

```bash
# From the project root
./sparse
Choose operation: 1) Add  2) Subtract  3) Multiply
Enter path to first matrix file: sample_inputs/A.txt
Enter path to second matrix file: sample_inputs/B.txt
```

* The program writes the result to `result.txt` in your current directory.

---

## 🗄️ File Format & Sample Data

```text
rows=4
cols=5
(0, 1, 10)
(1, 3, -5)
(3, 0, 7)
```

* **rows**: Number of rows (0-based indices go from `0` to `rows-1`).
* **cols**: Number of columns (0-based indices go from `0` to `cols-1`).
* Each entry: `(row_index, col_index, value)`

Sample data in `sample_inputs/`: `.txt` files paired by matching dimensions for addition/subtraction, or appropriate shapes for multiplication.

---

## ⚠️ Handling Header Mismatches

If you encounter **"Index out of bounds"** errors, it means your file’s `rows=` or `cols=` header is too small. To correct:

1. **Find the true maxima**:

   ```bash
   awk -F'[(), ]+' '/\(/ { if ($2>r) r=$2; if ($3>c) c=$3 } END { print "maxr=" (r+1) " maxc=" (c+1) }' sample_inputs/your_file.txt
   ```
2. **Update the header**:

   ```bash
   sed -i 's/^rows=.*/rows=<maxr>/' sample_inputs/your_file.txt
   sed -i 's/^cols=.*/cols=<maxc>/' sample_inputs/your_file.txt
   ```
3. **Re-run**:

   ```bash
   ./sparse
   ```

This ensures `rows` = maximum row index + 1, and `cols` = maximum column index + 1.

---

## 📂 Project Structure

```
📦 sparse-matrix
 ┣ 📂 sample_inputs   ← Your matrix files (.txt)
 ┃ ┣ 📄 easy_sample_03_1.txt
 ┃ ┣ 📄 easy_sample_03_2.txt
 ┃ ┣ 📄 matrixfile1.txt
 ┃ ┗ 📄 matrixfile3.txt
 ┣ 📄 SparseMatrix.cpp
 ┣ 📄 result.txt      ← Generated output
 ┣ 📄 README.md       ← You are here!
 ┗ 📄 LICENSE
```

---

## 🔍 Algorithmic Details

1. **Parsing**: Reads `rows=`, `cols=` header and entries `(r,c,v)`.
2. **Storage**: Each row holds a sorted `std::vector<Entry>`.
3. **Addition/Subtraction**: Two-pointer merge per row, skipping zeros.
4. **Multiplication**: Iterate nonzeros in A’s row, multiply with nonzeros in B’s corresponding rows.

---

## 🚀 Performance & Efficiency

* **Addition/Subtraction**: O(N\_A + N\_B) per row (N = nonzeros).
* **Multiplication**: O(∑*i N*{A,i}·logN\_{R,i} + N\_{B,k}).
* **Memory**: O(total nonzeros).

---

## 🤝 Contributing

1. Fork the repo
2. Create a feature branch
3. Commit & push your changes
4. Open a Pull Request

Follow the [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html) and include tests.

---

## 📝 License

This project is licensed under the **MIT License**. See [LICENSE](LICENSE).

---

## 📬 Contact & Support

Facilitator: Dr. Data Structures (\[[wdebela@alueducation.com](mailto:email@example.com)])

Open an issue for questions or suggestions. Happy coding! 🎉

