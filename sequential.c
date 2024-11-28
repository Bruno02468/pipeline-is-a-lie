#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Global variables
double *vetorA;
double *vetorB;
double *vetorC;
int tamanho_global;

void processa_vetor_a() {
    vetorA[0] = 3.0;  // Initial value
    for (int i = 1; i < tamanho_global; i++) {
        vetorA[i] = vetorA[i-1] + 2.0;
    }
}

void processa_vetor_b() {
    vetorB[0] = 5.0;  // Initial value
    for (int i = 1; i < tamanho_global; i++) {
        vetorB[i] = vetorB[i-1] + vetorA[i-2];
    }
}

void processa_vetor_c() {
    vetorC[0] = 7.0;  // Initial value
    for (int i = 1; i < tamanho_global; i++) {
        vetorC[i] = vetorC[i-1] + vetorB[i-2];
    }
}

int main(int argc, char* argv[]) {
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
    
    processa_vetor_a();
    processa_vetor_b();
    processa_vetor_c();
    
    clock_t fim = clock();
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

    // Output format optimized for parsing
    printf("Time: %.6f\n", tempo);
    printf("Vector validation:\n");
    
    // Print first 5 elements
    printf("A: ");
    for(int i = 0; i < 5 && i < tamanho_global; i++) {
        printf("%.2f ", vetorA[i]);
    }
    printf("... ");
    // Print last 5 elements
    for(int i = tamanho_global-5; i < tamanho_global; i++) {
        printf("%.2f ", vetorA[i]);
    }
    printf("\n");
    
    printf("B: ");
    for(int i = 0; i < 5 && i < tamanho_global; i++) {
        printf("%.2f ", vetorB[i]);
    }
    printf("... ");
    for(int i = tamanho_global-5; i < tamanho_global; i++) {
        printf("%.2f ", vetorB[i]);
    }
    printf("\n");
    
    printf("C: ");
    for(int i = 0; i < 5 && i < tamanho_global; i++) {
        printf("%.2f ", vetorC[i]);
    }
    printf("... ");
    for(int i = tamanho_global-5; i < tamanho_global; i++) {
        printf("%.2f ", vetorC[i]);
    }
    printf("\n");

    free(vetorA);
    free(vetorB);
    free(vetorC);

    return 0;
}