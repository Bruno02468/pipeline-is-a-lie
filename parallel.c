#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include <semaphore.h>

// Global variables
double *vetorA;
double *vetorB;
double *vetorC;
int tamanho_global;
sem_t *sem_ab;
sem_t *sem_bc;

void processa_vetor_a() {
    vetorA[0] = 3.0;
    sem_post(&sem_ab[0]);
    
    for (int i = 1; i < tamanho_global; i++) {
        vetorA[i] = vetorA[i-1] + 2.0;
        sem_post(&sem_ab[i]);
    }
}

void processa_vetor_b() {
    sem_wait(&sem_ab[0]);
    vetorB[0] = 5.0;
    sem_post(&sem_bc[0]);
    
    for (int i = 1; i < tamanho_global; i++) {
        sem_wait(&sem_ab[i]);
        vetorB[i] = vetorB[i-1] + vetorA[i-1];
        sem_post(&sem_bc[i]);
    }
}

void processa_vetor_c() {
    sem_wait(&sem_bc[0]);
    vetorC[0] = 7.0;
    
    for (int i = 1; i < tamanho_global; i++) {
        sem_wait(&sem_bc[i]);
        vetorC[i] = vetorC[i-1] + vetorB[i-1];
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

    // Initialize semaphores
    sem_ab = (sem_t*)malloc(tamanho_global * sizeof(sem_t));
    sem_bc = (sem_t*)malloc(tamanho_global * sizeof(sem_t));
    
    for(int i = 0; i < tamanho_global; i++) {
        sem_init(&sem_ab[i], 0, 0);
        sem_init(&sem_bc[i], 0, 0);
    }

    clock_t inicio = clock();

    #pragma omp parallel sections num_threads(3)
    {
        #pragma omp section
        processa_vetor_a();

        #pragma omp section
        processa_vetor_b();

        #pragma omp section
        processa_vetor_c();
    }

    clock_t fim = clock();
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("Time: %.6f\n", tempo);
    printf("Vector validation:\n");
    
    // print only C vector
    for (int i = 0; i < tamanho_global; i++) {
        printf("vetorC[%d]=%.2f; ", i, vetorC[i]);
    }
    printf("\n");

    // Cleanup
    for(int i = 0; i < tamanho_global; i++) {
        sem_destroy(&sem_ab[i]);
        sem_destroy(&sem_bc[i]);
    }
    free(sem_ab);
    free(sem_bc);
    free(vetorA);
    free(vetorB);
    free(vetorC);

    return 0;
}
