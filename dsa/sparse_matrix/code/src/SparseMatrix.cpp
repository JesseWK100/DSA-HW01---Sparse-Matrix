#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdexcept>
#include <algorithm>

struct Entry {
    int col;
    int value;
    bool operator<(const Entry& other) const {
        return col < other.col;
    }
};

class SparseMatrix {
private:
    int rows_, cols_;
    // For each row, a sorted vector of (col, value) entries
    std::vector<std::vector<Entry>> data_;

    static std::string trim(const std::string& s) {
        auto l = s.find_first_not_of(" \t\r\n");
        auto r = s.find_last_not_of(" \t\r\n");
        return (l == std::string::npos) ? "" : s.substr(l, r - l + 1);
    }

    static void parseHeader(const std::string& line, const std::string& prefix, int& out) {
        auto t = trim(line);
        if (t.substr(0, prefix.size()) != prefix)
            throw std::invalid_argument("Input file has wrong format");
        std::string num = t.substr(prefix.size());
        try {
            out = std::stoi(num);
        } catch (...) {
            throw std::invalid_argument("Input file has wrong format");
        }
    }

    void checkDimensionsMatch(const SparseMatrix& o) const {
        if (rows_ != o.rows_ || cols_ != o.cols_)
            throw std::invalid_argument("Matrix dimensions do not match for this operation");
    }

public:
    // Construct empty matrix
    SparseMatrix(int r = 0, int c = 0) : rows_(r), cols_(c), data_(r) {
        if (r < 0 || c < 0) throw std::invalid_argument("Invalid matrix size");
    }

    // Read from file
    SparseMatrix(const std::string& filePath) {
        std::ifstream in(filePath);
        if (!in) throw std::invalid_argument("Cannot open file: " + filePath);
        std::string line;
        // Read rows
        if (!std::getline(in, line)) throw std::invalid_argument("Input file has wrong format");
        parseHeader(line, "rows=", rows_);
        // Read cols
        if (!std::getline(in, line)) throw std::invalid_argument("Input file has wrong format");
        parseHeader(line, "cols=", cols_);
        data_.assign(rows_, {});
        // Read entries
        int lineNo = 2;
        while (std::getline(in, line)) {
            ++lineNo;
            line = trim(line);
            if (line.empty()) continue;
            if (line.front() != '(' || line.back() != ')')
                throw std::invalid_argument("Input file has wrong format at line " + std::to_string(lineNo));
            std::string body = line.substr(1, line.size() - 2);
            std::istringstream ss(body);
            int r, c, v;
            char comma1, comma2;
            if (!(ss >> r >> comma1 >> c >> comma2 >> v) || comma1 != ',' || comma2 != ',')
                throw std::invalid_argument("Input file has wrong format at line " + std::to_string(lineNo));
            if (r < 0 || r >= rows_ || c < 0 || c >= cols_)
                throw std::invalid_argument("Index out of bounds at line " + std::to_string(lineNo));
            data_[r].push_back({c, v});
        }
        // Sort each row by column
        for (auto& row : data_) {
            std::sort(row.begin(), row.end());
        }
    }

    int getElement(int r, int c) const {
        if (r < 0 || r >= rows_ || c < 0 || c >= cols_)
            throw std::out_of_range("getElement indices out of range");
        auto& row = data_[r];
        auto it = std::lower_bound(row.begin(), row.end(), Entry{c,0});
        return (it != row.end() && it->col == c) ? it->value : 0;
    }

    void setElement(int r, int c, int v) {
        if (r < 0 || r >= rows_ || c < 0 || c >= cols_)
            throw std::out_of_range("setElement indices out of range");
        auto& row = data_[r];
        auto it = std::lower_bound(row.begin(), row.end(), Entry{c,0});
        if (it != row.end() && it->col == c) {
            if (v == 0) row.erase(it);
            else it->value = v;
        } else {
            if (v != 0) row.insert(it, Entry{c, v});
        }
    }

    SparseMatrix add(const SparseMatrix& o) const {
        checkDimensionsMatch(o);
        SparseMatrix R(rows_, cols_);
        for (int i = 0; i < rows_; ++i) {
            // merge two sorted lists
            const auto& A = data_[i];
            const auto& B = o.data_[i];
            auto& C = R.data_[i];
            size_t p = 0, q = 0;
            while (p < A.size() || q < B.size()) {
                if (q == B.size() || (p < A.size() && A[p].col < B[q].col)) {
                    C.push_back(A[p++]);
                } else if (p == A.size() || (q < B.size() && B[q].col < A[p].col)) {
                    C.push_back(B[q++]);
                } else {
                    int s = A[p].value + B[q].value;
                    if (s != 0) C.push_back({A[p].col, s});
                    ++p; ++q;
                }
            }
        }
        return R;
    }

    SparseMatrix subtract(const SparseMatrix& o) const {
        checkDimensionsMatch(o);
        SparseMatrix R(rows_, cols_);
        for (int i = 0; i < rows_; ++i) {
            const auto& A = data_[i];
            const auto& B = o.data_[i];
            auto& C = R.data_[i];
            size_t p = 0, q = 0;
            while (p < A.size() || q < B.size()) {
                if (q == B.size() || (p < A.size() && A[p].col < B[q].col)) {
                    C.push_back(A[p++]);
                } else if (p == A.size() || (q < B.size() && B[q].col < A[p].col)) {
                    C.push_back({B[q].col, -B[q].value});
                    ++q;
                } else {
                    int d = A[p].value - B[q].value;
                    if (d != 0) C.push_back({A[p].col, d});
                    ++p; ++q;
                }
            }
        }
        return R;
    }

    SparseMatrix multiply(const SparseMatrix& o) const {
        if (cols_ != o.rows_)
            throw std::invalid_argument("Matrix dimensions do not allow multiplication");
        SparseMatrix R(rows_, o.cols_);
        // For each row i in A
        for (int i = 0; i < rows_; ++i) {
            // For each nonzero in A row i
            for (auto& eA : data_[i]) {
                int k = eA.col;
                int vA = eA.value;
                // For each nonzero in B row k
                for (auto& eB : o.data_[k]) {
                    int j = eB.col;
                    int vB = eB.value;
                    int prev = R.getElement(i, j);
                    R.setElement(i, j, prev + vA * vB);
                }
            }
        }
        return R;
    }

    void writeToFile(const std::string& filePath) const {
        std::ofstream out(filePath);
        if (!out) throw std::runtime_error("Cannot open output file");
        out << "rows=" << rows_ << "\n";
        out << "cols=" << cols_ << "\n";
        for (int i = 0; i < rows_; ++i) {
            for (auto& e : data_[i]) {
                out << "(" << i << ", " << e.col << ", " << e.value << ")\n";
            }
        }
    }
};

int main() {
    try {
        std::cout << "Choose operation: 1) Add  2) Subtract  3) Multiply\n";
        int choice; 
        std::cin >> choice;
        if (choice < 1 || choice > 3) throw std::invalid_argument("Invalid operation choice");

        std::string fileA, fileB;
        std::cout << "Enter path to first matrix file: ";
        std::cin >> fileA;
        std::cout << "Enter path to second matrix file: ";
        std::cin >> fileB;

        SparseMatrix A(fileA), B(fileB), C;
        if (choice == 1)      C = A.add(B);
        else if (choice == 2) C = A.subtract(B);
        else                  C = A.multiply(B);

        C.writeToFile("result.txt");
        std::cout << "Operation successful. Result written to result.txt\n";
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << "\n";
        return 1;
    }
    return 0;
}
