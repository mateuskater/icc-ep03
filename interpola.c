#include <stdio.h>
#include <stdlib.h>

void print_polinomio(double *poli, int grau){
    char sinal;
    printf("%lfx^%d ", poli[grau],grau);
    for (int i = grau-1; i >= 0; i--){
        if (poli[i] < 0){
            sinal = '-';
            poli[i] *= -1;
        }else{ sinal = '+';}
        printf("%c %lfx^%d ",sinal, poli[i], i);
    }
    printf("\n");
}

double lagrange(int n, double x[], double y[], double xi) {
    double result = 0.0;

    for (int i = 0; i < n; i++) {
        double term = y[i];
        for (int j = 0; j < n; j++) {
            if (j != i) {
                term = term * (xi - x[j]) / (x[i] - x[j]);
            }
        }
        result += term;
    }

    return result;
}

void read_matrix(double **A, int n){
    for (int i = 0; i < n; i++){
        scanf("%lf\n", A[i][0]); // le x
        scanf("%lf\n",A[i][1]); // le f(x)
    }
    getchar();
}

int main(int argc, char **argv){
    double **tabela; // tabela de pontos
    int N; // numero de pontos
    double xe = atof(argv[1]);
    read_matrix(tabela,N);

}
