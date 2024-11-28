#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Global variables
double *vetorA;
double *vetorB;
double *vetorC;
int tamanho_global;

void processa_vetores() {
    int i;
    double a = 3.0, b = 5.0;
    vetorC[0] = 7.0;
    for (i = 1; i < tamanho_global; i++) {
        vetorC[i] = vetorC[i-1] + b;
        b += a;
        a += 2.0;
    }
}

int main(int argc, char* argv[]) {
    int i;
    if (argc != 2) {
        printf("Usage: %s vector_size\n", argv[0]);
        return 1;
    }

    tamanho_global = atoi(argv[1]);

    // Allocate memory for vectors
    vetorA = (double*)malloc(tamanho_global * sizeof(double));
    vetorB = (double*)malloc(tamanho_global * sizeof(double));
    vetorC = (double*)malloc(tamanho_global * sizeof(double));

    clock_t inicio = clock();
    
    processa_vetores();
    
    clock_t fim = clock();
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

    // Output format optimized for parsing
    printf("Time: %.6f\n", tempo);
    printf("Vector validation:\n");
    
    // print only C vector
    for (i = 0; i < tamanho_global; i++) {
        printf("vetorC[%d]=%.2f; ", i, vetorC[i]);
    }
    
    printf("\n");

    free(vetorA);
    free(vetorB);
    free(vetorC);

    return 0;
}
