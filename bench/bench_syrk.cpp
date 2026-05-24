#include "../include/syrk.hpp"
#include <cblas.h>

#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <iomanip>
#include <cmath>
#include <cstdlib>

template<typename T>
void fill_random(std::vector<T>& v) {
    std::mt19937 gen(42);
    std::uniform_real_distribution<T> dist(-1.0, 1.0);
    for (auto& x : v) {
        x = dist(gen);
    }
}

template<typename T>
double geometric_mean(const std::vector<T>& values) {
    double sum_logs = 0.0;
    for (const auto& v : values) {
        sum_logs += std::log(v);
    }
    return std::exp(sum_logs / values.size());
}

double benchmark_custom_float(
    int n, int k,
    float alpha, float beta,
    const std::vector<float>& A_init,
    const std::vector<float>& C_init
) {
    std::vector<float> A = A_init;
    std::vector<float> C = C_init;

    auto start = std::chrono::high_resolution_clock::now();

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

    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double>(end - start).count();
}

double benchmark_openblas_float(
    int n, int k,
    float alpha, float beta,
    const std::vector<float>& A_init,
    const std::vector<float>& C_init
) {
    std::vector<float> A = A_init;
    std::vector<float> C = C_init;

    auto start = std::chrono::high_resolution_clock::now();

    cblas_ssyrk(
        CblasRowMajor,
        CblasUpper,
        CblasNoTrans,
        n,
        k,
        alpha,
        A.data(),
        k,
        beta,
        C.data(),
        n
    );

    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double>(end - start).count();
}

double benchmark_custom_double(
    int n, int k,
    double alpha, double beta,
    const std::vector<double>& A_init,
    const std::vector<double>& C_init
) {
    std::vector<double> A = A_init;
    std::vector<double> C = C_init;

    auto start = std::chrono::high_resolution_clock::now();

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

    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double>(end - start).count();
}

double benchmark_openblas_double(
    int n, int k,
    double alpha, double beta,
    const std::vector<double>& A_init,
    const std::vector<double>& C_init
) {
    std::vector<double> A = A_init;
    std::vector<double> C = C_init;

    auto start = std::chrono::high_resolution_clock::now();

    cblas_dsyrk(
        CblasRowMajor,
        CblasUpper,
        CblasNoTrans,
        n,
        k,
        alpha,
        A.data(),
        k,
        beta,
        C.data(),
        n
    );

    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double>(end - start).count();
}

void run_float_test(int n, int k) {
    float alpha = 1.0f;
    float beta = 1.0f;

    std::vector<float> A(n * k);
    std::vector<float> C(n * n);

    fill_random(A);
    fill_random(C);

    std::vector<double> relative_perf;

    std::cout << "\n===== FLOAT SYRK TEST =====\n";
    std::cout << "n = " << n << ", k = " << k << "\n\n";
    std::cout << std::setw(5) << "Run"
              << std::setw(18) << "Custom (s)"
              << std::setw(18) << "OpenBLAS (s)"
              << std::setw(18) << "Relative (%)"
              << "\n";

    for (int i = 1; i <= 10; ++i) {
        double t_custom = benchmark_custom_float(n, k, alpha, beta, A, C);
        double t_blas = benchmark_openblas_float(n, k, alpha, beta, A, C);

        double perf = (t_blas / t_custom) * 100.0;
        relative_perf.push_back(perf);

        std::cout << std::setw(5) << i
                  << std::setw(18) << std::fixed << std::setprecision(6) << t_custom
                  << std::setw(18) << std::fixed << std::setprecision(6) << t_blas
                  << std::setw(18) << std::fixed << std::setprecision(2) << perf
                  << "\n";
    }

    std::cout << "\nGeometric mean relative performance: "
              << std::fixed << std::setprecision(2)
              << geometric_mean(relative_perf) << "%\n";
}

void run_double_test(int n, int k) {
    double alpha = 1.0;
    double beta = 1.0;

    std::vector<double> A(n * k);
    std::vector<double> C(n * n);

    fill_random(A);
    fill_random(C);

    std::vector<double> relative_perf;

    std::cout << "\n===== DOUBLE SYRK TEST =====\n";
    std::cout << "n = " << n << ", k = " << k << "\n\n";
    std::cout << std::setw(5) << "Run"
              << std::setw(18) << "Custom (s)"
              << std::setw(18) << "OpenBLAS (s)"
              << std::setw(18) << "Relative (%)"
              << "\n";

    for (int i = 1; i <= 10; ++i) {
        double t_custom = benchmark_custom_double(n, k, alpha, beta, A, C);
        double t_blas = benchmark_openblas_double(n, k, alpha, beta, A, C);

        double perf = (t_blas / t_custom) * 100.0;
        relative_perf.push_back(perf);

        std::cout << std::setw(5) << i
                  << std::setw(18) << std::fixed << std::setprecision(6) << t_custom
                  << std::setw(18) << std::fixed << std::setprecision(6) << t_blas
                  << std::setw(18) << std::fixed << std::setprecision(2) << perf
                  << "\n";
    }

    std::cout << "\nGeometric mean relative performance: "
              << std::fixed << std::setprecision(2)
              << geometric_mean(relative_perf) << "%\n";
}

int main() {
    const char* threads = std::getenv("OPENBLAS_NUM_THREADS");
    std::cout << "OPENBLAS_NUM_THREADS = "
              << (threads ? threads : "not set") << "\n";

    run_float_test(3328, 3328);
    run_double_test(3328, 3328);

    return 0;
}
