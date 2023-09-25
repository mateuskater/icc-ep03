#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// Definir a estrutura para representar pontos (x, f(x))
typedef struct {
    double x;
    double fx;
} Point;

// Função para calcular o polinômio de Lagrange
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

// Função para calcular o polinômio de Newton
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

int main() {
    int N;
    printf("Informe a quantidade de pontos N: ");
    scanf("%d", &N);

    Point* table = malloc(N * sizeof(Point));
    printf("Informe os pontos (x, f(x)):\n");
    for (int i = 0; i < N; i++) {
        scanf("%lf %lf", &table[i].x, &table[i].fx);
    }

    double xe;
    printf("Informe o valor de xe para interpolação: ");
    scanf("%lf", &xe);

    // Medir o tempo para o método de Lagrange
    clock_t start = clock();
    double lagrangeResult = lagrangeInterpolation(table, N, xe);
    clock_t end = clock();
    double lagrangeTime = (double)(end - start) * 1000.0 / CLOCKS_PER_SEC;

    // Medir o tempo para o método de Newton
    start = clock();
    double newtonResult = newtonInterpolation(table, N, xe);
    end = clock();
    double newtonTime = (double)(end - start) * 1000.0 / CLOCKS_PER_SEC;

    printf("Resultado da interpolação por Lagrange: %.4lf\n", lagrangeResult);
    printf("Tempo gasto em milisegundos para Lagrange: %.4lf\n", lagrangeTime);
    printf("Resultado da interpolação por Newton: %.4lf\n", newtonResult);
    printf("Tempo gasto em milisegundos para Newton: %.4lf\n", newtonTime);

    free(table);
    return 0;
}
