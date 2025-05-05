#include<stdio.h>
#include<omp.h>

#define T 3

int main(int argc ,char *argv[]){

int thread_num;


thread_num = omp_get_thread_num();
printf("Área sequencial - Thread %d\n", thread_num);

#pragma omp parallel private(thread_num) num_threads(T)
{
thread_num = omp_get_thread_num();
printf("Thread %d - Hello World\n",thread_num);


}



}