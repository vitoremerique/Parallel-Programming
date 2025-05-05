#include<stdio.h>
#include <stdlib.h>
#include<omp.h>


int main(int argc, char *argv[]){

int tam,*vetor,seed,i;
int soma_reduction=0;
int soma_shared=0;
double wtime;


if(argc !=3){
printf("Argumento errado o padrão é [Tamanho do vetor] [Seed]");

}

tam = atoi(argv[1]); // tamanho do vetor
seed = atoi(argv[2]); // valor mais pseudoaleatório

vetor = (int*)malloc(tam*sizeof(int)); // alocando espaço de memória para o vetor

srand(seed);

for(i=0; i<tam;i++){
    vetor[i] = rand()%10;
    printf("%d ",vetor[i]) ;// populando o vetor com valores pseudoaleatórios
}

printf("\n");
wtime = omp_get_wtime();
#pragma omp parallel for private(i) reduction(+:soma_reduction)
for(i=0;i<tam;i++){
    soma_reduction+=vetor[i];
}

wtime = omp_get_wtime() - wtime;


printf("Área sequencial - Soma com reduction = %d\n",soma_reduction);
printf("Tempo de execução %f\n",wtime);


fflush(0);


wtime = omp_get_wtime();

#pragma omp parallel for private(i) shared(soma_shared)
for(i=0;i<tam;i++)
{
    #pragma omp critical(rc_soma)
    soma_shared += vetor[i];
}

wtime = omp_get_wtime() - wtime;

printf("\n");
printf("-------------------\n");

printf("Área sequencial - soma = %d\n",soma_shared);
printf("Tempo de execução = %f\n",wtime);
}