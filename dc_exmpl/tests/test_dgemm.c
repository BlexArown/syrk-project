#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cblas.h>
#include <assert.h>

#define N 3

int main() {
    double A[N*N] = {
        1,2,3,
        4,5,6,
        7,8,9
    };

    double B[N*N] = {
        9,8,7,
        6,5,4,
        3,2,1
    };

    double C[N*N] = {0};
    double C_ref[N*N] = {0};

    cblas_dgemm(
        CblasRowMajor,
        CblasNoTrans,
        CblasNoTrans,
        N, N, N,
        1.0,
        A, N,
        B, N,
        0.0,
        C, N
    );

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            double sum = 0;
            for(int k = 0; k < N; k++) {
                sum += A[i*N + k] * B[k*N + j];
            }
            C_ref[i*N + j] = sum;
        }
    }

    for(int i = 0; i < N*N; i++) {
        if(fabs(C[i] - C_ref[i]) > 1e-9) {
            printf("Ошибка! Индекс %d\n", i);
            printf("OpenBLAS: %lf\n", C[i]);
            printf("Reference: %lf\n", C_ref[i]);
            return 1;
        }
    }

    printf("Тест cblas_dgemm пройден успешно\n");

    return 0;
}
