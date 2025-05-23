#include<stdio.h>
#include<mpi.h>

int main(int argc, char* argv[]){

int myrank,size, soma,subtração,multi,div;
MPI_Init(&argc,&argv);



int a = 10;
int b = 2;


MPI_Comm_size(MPI_COMM_WORLD,&size);
MPI_Comm_rank(MPI_COMM_WORLD,&myrank);


printf("Processo(%d) O programa possui %d processos\n",myrank,size);

if(myrank ==0){

printf("Processo(%d) realiza a operação de soma, a+b= %d\n",myrank,a+b);
}

if(myrank ==1){
    
printf("Processo(%d) realiza a operação de subtração, a+b= %d\n",myrank,a-b);
}

if(myrank ==2){
    
printf("Processo(%d) realiza a operação de multiplicação, a*b= %d\n",myrank,a*b);
}

if(myrank ==3){
    
printf("Processo(%d) realiza a operação de soma, a/b= %d\n",myrank,a/b);
}

MPI_Finalize();

}