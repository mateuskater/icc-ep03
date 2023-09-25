#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <likwid.h>

typedef struct {
    double x;
    double fx;
} Point;

double timestamp(void){
    struct timespec tp;
    clock_gettime(CLOCK_MONOTONIC_RAW, &tp);
    return ((double)tp.tv_sec*1.0e3 + (double)tp.tv_nsec*1.0e-6);
}

double lagrangeInterpolation(Point* table, int N, double xe) {
    double result = 0.0;
    for (int i = 0; i < N; i++) {
        double term = table[i].fx;
        for (int j = 0; j < N; j++) {
            if (j != i) {
                term *= (xe - table[j].x) / (table[i].x - table[j].x);
            }
        }
        result += term;
    }
    return result;
}

double newtonInterpolation(Point* table, int N, double xe) {
    double result = table[0].fx;
    double* dividedDifferences = malloc(N * sizeof(double));

    for (int i = 0; i < N; i++) {
        dividedDifferences[i] = table[i].fx;
    }

    for (int i = 1; i < N; i++) {
        for (int j = N - 1; j >= i; j--) {
            dividedDifferences[j] = (dividedDifferences[j] - dividedDifferences[j - 1]) / (table[j].x - table[j - i].x);
        }
        result += dividedDifferences[i] * (xe - table[i - 1].x);
    }

    free(dividedDifferences);
    return result;
}

int main(int argc, char **argv) {
    LIKWID_MARKER_INIT;
    int N;
    double start, end;
    printf("Insira N.");
    scanf("%d", &N);

    Point* table = malloc(N * sizeof(Point));
    printf("Insira os pontos (x, f(x)).\n");
    for (int i = 0; i < N; i++) {
        scanf("%lf %lf", &table[i].x, &table[i].fx);
    }

    double xe = atoi(argv[1]);

    LIKWID_MARKER_START("lagrange");
    start = timestamp();
    double lagrangeResult = lagrangeInterpolation(table, N, xe);
    end = timestamp();
    LIKWID_MARKER_STOP("lagrange");

    printf("Tempo gasto para Lagrange: %lf\n",end-start);

    // Medir o tempo para o método de Newton
    LIKWID_MARKER_START("newton");
    start = timestamp();
    double newtonResult = newtonInterpolation(table, N, xe);
    end = timestamp();
    LIKWID_MARKER_STOP("newton");

    printf("Tempo gasto para newton: %lf\n",end-start);

    printf("Resultado da interpolação por Lagrange: %.4lf\n", lagrangeResult);
    printf("Resultado da interpolação por Newton: %.4lf\n", newtonResult);

    free(table);
    return 0;
}
