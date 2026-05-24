#pragma once

enum class Uplo {
    Upper,
    Lower
};

enum class Transpose {
    NoTrans,
    Trans
};

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
);
