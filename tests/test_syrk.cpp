#include "../include/syrk.hpp"
#include <iostream>
#include <vector>
#include <cmath>

bool almost_equal(double a, double b, double eps = 1e-6) {
    return std::fabs(a - b) < eps;
}

int main() {
    int n = 2;
    int k = 2;
    double alpha = 1.0;
    double beta = 0.0;

    std::vector<double> A = {
        1, 2,
        3, 4
    };

    std::vector<double> C(n * n, 0.0);

    syrk_custom<double>(
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

    if (!almost_equal(C[0], 5.0)) {
        std::cout << "Test failed: C[0] != 5\n";
        return 1;
    }

    if (!almost_equal(C[1], 11.0)) {
        std::cout << "Test failed: C[1] != 11\n";
        return 1;
    }

    std::cout << "Test passed\n";
    return 0;
}
