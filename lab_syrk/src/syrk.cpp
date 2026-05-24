#include "../include/syrk.hpp"
#include <stdexcept>

template<typename T>
void syrk_custom(
    Uplo uplo,
    Transpose trans,
    int n,
    int k,
    T alpha,
    const T* A,
    int lda,
    T beta,
    T* C,
    int ldc
) {
    if (!A || !C) {
        throw std::invalid_argument("A or C is null");
    }

    if (n < 0 || k < 0 || lda <= 0 || ldc <= 0) {
        throw std::invalid_argument("Invalid matrix sizes");
    }

    if (n == 0) {
        return;
    }

    if (trans == Transpose::NoTrans) {
        for (int i = 0; i < n; ++i) {
            if (uplo == Uplo::Upper) {
                for (int j = i; j < n; ++j) {
                    T sum = 0;
                    for (int p = 0; p < k; ++p) {
                        sum += A[i * lda + p] * A[j * lda + p];
                    }
                    C[i * ldc + j] = alpha * sum + beta * C[i * ldc + j];
                }
            } else {
                for (int j = 0; j <= i; ++j) {
                    T sum = 0;
                    for (int p = 0; p < k; ++p) {
                        sum += A[i * lda + p] * A[j * lda + p];
                    }
                    C[i * ldc + j] = alpha * sum + beta * C[i * ldc + j];
                }
            }
        }
    } else {
        for (int i = 0; i < n; ++i) {
            if (uplo == Uplo::Upper) {
                for (int j = i; j < n; ++j) {
                    T sum = 0;
                    for (int p = 0; p < k; ++p) {
                        sum += A[p * lda + i] * A[p * lda + j];
                    }
                    C[i * ldc + j] = alpha * sum + beta * C[i * ldc + j];
                }
            } else {
                for (int j = 0; j <= i; ++j) {
                    T sum = 0;
                    for (int p = 0; p < k; ++p) {
                        sum += A[p * lda + i] * A[p * lda + j];
                    }
                    C[i * ldc + j] = alpha * sum + beta * C[i * ldc + j];
                }
            }
        }
    }
}

template void syrk_custom<float>(
    Uplo, Transpose, int, int, float, const float*, int, float, float*, int
);

template void syrk_custom<double>(
    Uplo, Transpose, int, int, double, const double*, int, double, double*, int
);
