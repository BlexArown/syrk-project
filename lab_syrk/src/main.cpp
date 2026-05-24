#include "../include/syrk.hpp"
#include <iostream>
#include <vector>

template<typename T>
void print_matrix(const std::vector<T>& M, int rows, int cols, int ld) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << M[i * ld + j] << " ";
        }
        std::cout << "\n";
    }
}

int main() {
    int n = 3;
    int k = 2;
    float alpha = 1.0f;
    float beta = 0.0f;

    std::vector<float> A = {
        1, 2,
        3, 4,
        5, 6
    };

    std::vector<float> C(n * n, 0.0f);

    syrk_custom<float>(
        Uplo::Upper,
        Transpose::NoTrans,
        n,
        k,
        alpha,
        A.data(),
        k,
        beta,
        C.data(),
        n
    );

    std::cout << "Matrix C:\n";
    print_matrix(C, n, n, n);

    return 0;
}
