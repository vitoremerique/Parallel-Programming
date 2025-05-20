//1) Dado um vetor vet[TAM], determinar quantos nrs maiores que vet[K] existem em
//vet e em quais posições eles estão, conforme especificação.



#include<stdio.h>

#include<stdlib.h>

#define tam 10

int main(int argc, char *argv[]){
int vet[tam],seed, K, referencia,contador;
K=3;
contador = 0;

seed = 5;

srand(seed);
    printf("[");
    for(int i =0 ; i<tam; i++){

        vet[i] = rand()%50;
        if(i==tam-1){
            printf("%d", vet[i]);
        }else{
        printf("%d,", vet[i]);
        }

    }
    printf("]\n");

referencia = vet[3];

printf("O valor de da posição %d = %d\n",K,referencia);

for(int j =0; j<tam;j++){

if(vet[j]> referencia){
    printf("Posição %d (valor = %d)\n", j, vet[j]);
    contador++;
}

}

printf("Total de valores maiores que vet[%d]: %d", K, contador);



}