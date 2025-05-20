//2) Faça um programa concorrente em C/MPI que implemente um Token Ring de
//processos, conforme especificação.


//mpicc exercicio_2_tokenring.c -o exercicio_2_tokenring
//mpirun -np 4 exercicio_2_tokenring
////mpirun -np 10 --oversubscribe exercicio_2_tokenring

#include<stdio.h>
#include<mpi.h>


int main(int argc, char* argv[]){
int size, myrank,token;
MPI_Status status;

MPI_Init(&argc, &argv);
MPI_Comm_size(MPI_COMM_WORLD, &size);
MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

if(myrank == 0){

    
        token = 0;
        
        MPI_Send(&token, 1, MPI_INT,(myrank+1)%size,0,MPI_COMM_WORLD);
        printf("P(%d) iniciou o token\n",myrank);
        MPI_Recv(&token,1,MPI_INT,myrank -1,0,MPI_COMM_WORLD,&status);
        printf("P(%d)recebeu o token, valor=%d\n",myrank,token);

        for(int i=0;i<4;i++){
        token++;
        printf("P(%d)(%d) atualizou o token, valor=%d\n",myrank,i,token);

        }

    
}else{

    
        MPI_Recv(&token,1,MPI_INT,(myrank -1),0,MPI_COMM_WORLD,&status);
        printf("P(%d)recebeu o token, valor=%d\n",myrank,token);

        for(int i=0;i<4;i++){
        token++;
        printf("P(%d)(%d) atualizou o token, valor=%d\n",myrank,i,token);

        }
       
        MPI_Send(&token, 1,MPI_INT, (myrank+1)%size,0,MPI_COMM_WORLD);  
        



    

}


MPI_Finalize();



}