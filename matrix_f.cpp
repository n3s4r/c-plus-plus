#include <iostream>
#include <vector>

typedef std::vector<std::vector<int>> Matrix;

Matrix transpose(const Matrix& mat) {
    int rows = mat.size();
    int cols = mat[0].size();
    // Initialize a vector with 'cols' rows and 'rows' columns
    Matrix tras(cols, std::vector<int>(rows));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            tras[j][i] = mat[i][j];
        }
    }
    return tras;
}

int main() {
    Matrix matrix = {{1, 2}, {3, 4}, {5, 6}};
    Matrix result = transpose(matrix);

    for (const auto& row : result) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}
