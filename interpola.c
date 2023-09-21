#include <stdio.h>
#include <stdlib.h>

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
