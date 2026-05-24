#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cblas.h>
#include <assert.h>

#define EPS 1e-9

void test_daxpy() {
    int n = 3;
    double x[3] = {1,2,3};
    double y[3] = {4,5,6};
    double y_ref[3] = {4,5,6};

    cblas_daxpy(n, 2.0, x, 1, y, 1);

    for(int i=0;i<n;i++) {
        y_ref[i] = y_ref[i] + 2.0 * x[i];
        assert(fabs(y[i] - y_ref[i]) < EPS);
    }

    printf("daxpy выполнен\n");
}

void test_ddot() {
    int n = 3;
    double x[3] = {1,2,3};
    double y[3] = {4,5,6};

    double res = cblas_ddot(n, x, 1, y, 1);

    double expected = 1*4 + 2*5 + 3*6;

    assert(fabs(res - expected) < EPS);

    printf("ddot выполнен\n");
}

void test_dscal() {
    int n = 3;
    double x[3] = {1,2,3};

    cblas_dscal(n, 3.0, x, 1);

    for(int i=0;i<n;i++) {
        assert(fabs(x[i] - (3.0*(i+1))) < EPS);
    }

    printf("dscal выполнен\n");
}

void test_dcopy() {
    int n = 3;
    double x[3] = {1,2,3};
    double y[3] = {0};

    cblas_dcopy(n, x, 1, y, 1);

    for(int i=0;i<n;i++) {
        assert(x[i] == y[i]);
    }

    printf("dcopy выполнен\n");
}

void test_dnrm2() {
    int n = 2;
    double x[2] = {3,4};

    double res = cblas_dnrm2(n, x, 1);

    double expected = 5.0;
    assert(fabs(res - expected) < EPS);

    printf("dnrm2 выполнен\n");
}

void test_dgemv() {
    int m = 2;
    int n = 2;

    double A[4] = {
        1,2,
        3,4
    };

    double x[2] = {1,1};
    double y[2] = {0,0};

    cblas_dgemv(
        CblasRowMajor,
        CblasNoTrans,
        m, n,
        1.0,
        A, n,
        x, 1,
        0.0,
        y, 1
    );

    double expected0 = 1*1 + 2*1;
    double expected1 = 3*1 + 4*1;

    assert(fabs(y[0] - expected0) < EPS);
    assert(fabs(y[1] - expected1) < EPS);

    printf("dgemv выполнен\n");
}

void test_dgemm() {
    int n = 2;

    double A[4] = {
        1,2,
        3,4
    };

    double B[4] = {
        5,6,
        7,8
    };

    double C[4] = {0};

    cblas_dgemm(
        CblasRowMajor,
        CblasNoTrans,
        CblasNoTrans,
        n, n, n,
        1.0,
        A, n,
        B, n,
        0.0,
        C, n
    );

    double expected00 = 1*5 + 2*7;
    double expected01 = 1*6 + 2*8;
    double expected10 = 3*5 + 4*7;
    double expected11 = 3*6 + 4*8;

    assert(fabs(C[0] - expected00) < EPS);
    assert(fabs(C[1] - expected01) < EPS);
    assert(fabs(C[2] - expected10) < EPS);
    assert(fabs(C[3] - expected11) < EPS);

    printf("dgemm прошел\n");
}

int main() {

    printf("=== Запуск интерфейсных тестов CBLAS ===\n\n");

    test_daxpy();
    test_ddot();
    test_dscal();
    test_dcopy();
    test_dnrm2();
    test_dgemv();
    test_dgemm();

    printf("\nВсе тесты пройдены успешно\n");

    return 0;
}
