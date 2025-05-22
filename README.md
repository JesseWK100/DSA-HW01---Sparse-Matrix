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
6. [Project Structure](#-project-structure)
7. [Algorithmic Details](#-algorithmic-details)
8. [Performance & Efficiency](#-performance--efficiency)
9. [Contributing](#-contributing)
10. [License](#-license)
11. [Contact & Support](#-contact--support)

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

* **Compiler**: `g++ (GCC) >= 4.8` or any C++11‑compliant compiler
* **Platform**: Linux, macOS, or Windows (with MinGW/Cygwin)
* **Memory**: Adequate RAM to hold your sparse data (large dense matrices discouraged)

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

4. **Run the executable** (next section)

---

## 🎮 Usage Guide

### 🏗️ Compiling the Code

```bash
# From the root directory
g++ -std=c++11 -O2 SparseMatrix.cpp -o sparse
```

*The `-O2` flag optimizes for speed; remove if debugging.*

### ▶️ Running the Program

```bash
# ./sparse
Choose operation: 1) Add  2) Subtract  3) Multiply
Enter path to first matrix file: sample_inputs/A.txt
Enter path to second matrix file: sample_inputs/B.txt
# Result will be saved to result.txt
```

* **Result File**: `result.txt` in the same format as input.

---

## 🗄️ File Format & Sample Data

```text
rows=4
cols=5
(0, 1, 10)
(1, 3, -5)
(3, 0, 7)
```

* **rows**: Number of matrix rows
* **cols**: Number of matrix columns
* Each entry: `(row_index, col_index, value)`
* Indices are **0-based**

Sample data resides in `sample_inputs/`:

* `A.txt`, `B.txt`, …

---

## 📂 Project Structure

```
📦 sparse-matrix
 ┣ 📂 sample_inputs
 ┃ ┣ 📄 A.txt
 ┃ ┗ 📄 B.txt
 ┣ 📄 SparseMatrix.cpp
 ┣ 📄 result.txt      # Generated output
 ┣ 📄 README.md       # ← You are here!
 ┗ 📄 LICENSE
```

---

## 🔍 Algorithmic Details

1. **Parsing**: Reads header lines `rows=<n>`, `cols=<m>` and then entries `(r,c,v)`.
2. **Storage**: Each row holds a sorted `std::vector<Entry>` for quick merge and lookup.
3. **Addition/Subtraction**: Two‐pointer merge of the per‐row lists, summing or subtracting values; skips zeros.
4. **Multiplication**: For each nonzero in `A[i][k]`, scan nonzeros in row `k` of `B`, accumulating products in result row `i`.

---

## 🚀 Performance & Efficiency

* **Time Complexity**:

  * Addition/Subtraction: O(N<sub>A</sub> + N<sub>B</sub>) per row (N = nonzeros)
  * Multiplication: O(∑<sub>i</sub> N<sub>A,i</sub> × log N<sub>R,i</sub> + N<sub>B,k</sub>)
* **Memory**: O(total nonzero entries)

*Benchmarks coming soon… stay tuned!* 🚀

---

## 🤝 Contributing

1. Fork the repo
2. Create a feature branch: `git checkout -b feature/YourFeature`
3. Commit your changes: `git commit -m 'Add awesome feature'`
4. Push to branch: `git push origin feature/YourFeature`
5. Open a Pull Request

Please follow the [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html) and include unit tests.

---

## 📝 License

This project is licensed under the **MIT License**. See [LICENSE](LICENSE) for details.

---

## 📬 Contact & Support

🤗 **Facilitator**: Dr. Data Structures (\[[wdebela@alueducation.com](mailto:email@example.com)])

Feel free to open an issue or email for questions, suggestions, or to share your results. Happy Coding! 🎉

