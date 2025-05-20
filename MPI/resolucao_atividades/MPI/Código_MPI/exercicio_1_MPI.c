//1) Dado um vetor vet[TAM], determinar quantos nrs maiores que vet[K] existem em
//vet e em quais posições eles estão, conforme especificação.



#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>

#define TAM 10

int main(int argc, char *argv[]) {
    int vet[TAM];
    int seed = 5, K = 3, referencia, contador = 0;
    int myrank, size, src, dest, mstag;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

    if (size < 2) {
        if (myrank == 0) {
            printf("Este programa requer pelo menos 2 processos.\n");
        }
        MPI_Finalize();
        return 0;
    }

    if (myrank == 0) {
        src = dest = 1;
        srand(seed);

        printf("Vetor gerado no Processo %d: [",myrank);
        for (int i = 0; i < TAM; i++) {
            vet[i] = rand() % 50;
            printf("%d%s", vet[i], (i < TAM - 1) ? ", " : "]\n");
        }

        // Envia vetor para o processo 1
        mstag = 0;
        MPI_Send(vet, TAM, MPI_INT, dest, mstag, MPI_COMM_WORLD);

        // Recebe contador do processo 1
        mstag = 2;
        MPI_Recv(&contador, 1, MPI_INT, src, mstag, MPI_COMM_WORLD, &status);

        printf("Rank(%d) - Total de valores maiores que vet[%d] = %d: %d\n", myrank,K, vet[K], contador);
    } else if (myrank == 1) {
        src = dest = 0;

        // Recebe o vetor
        mstag = 0;
        MPI_Recv(vet, TAM, MPI_INT, src, mstag, MPI_COMM_WORLD, &status);

        referencia = vet[K];
        printf("P(%d): Referência vet[%d] = %d\n", myrank,K, referencia);

        for (int j = 0; j < TAM; j++) {
            if (vet[j] > referencia) {
                printf("P1: vet[%d] = %d é maior que %d\n", j, vet[j], referencia);
                contador++;
            }
        }

        // Envia contador de volta para o processo 0
        mstag = 2;
        MPI_Send(&contador, 1, MPI_INT, dest, mstag, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
